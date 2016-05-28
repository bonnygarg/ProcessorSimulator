#include "TraceCompilerFirstPass.h"

#include <SimulatorEngine\TraceCompiler\TraceCompilerSimulatorEngine.h>

#include <Operation\OutgoingEdges\ConditionalCallOutgoingEdges.h>
#include <Operation\OutgoingEdges\ConditionalJumpOutgoingEdges.h>
#include <Operation\OutgoingEdges\ConditionalReturnOutgoingEdges.h>
#include <Operation\OutgoingEdges\NextOutgoingEdges.h>
#include <Operation\OutgoingEdges\NonCompilableOutgoingEdges.h>
#include <Operation\OutgoingEdges\NoneOutgoingEdges.h>
#include <Operation\OutgoingEdges\OutgoingEdges.h>
#include <Operation\OutgoingEdges\UnconditionalCallOutgoingEdges.h>
#include <Operation\OutgoingEdges\UnconditionalJumpOutgoingEdges.h>
#include <Operation\OutgoingEdges\UnconditionalReturnOutgoingEdges.h>


TraceCompilerFirstPass::TraceCompilerFirstPass() :
	isEndOfBasicBlockFound_(false),
	address_(0),
	simulationUnitTable_(nullptr)
{}

void TraceCompilerFirstPass::Perform(State * s, Address startFromAddress, Decoder & decoder, std::unordered_map<Address, std::shared_ptr<SimulationUnit>>* simulationUnitTable, TraceCompilerSimulatorEngine & simulatorEngine)
{
	s_ = s;
	simulationUnitTable_ = simulationUnitTable;

	discoveredBlockStartAddresses_.clear();
	while (toProcessStartAddresses_.empty() == false)
		toProcessStartAddresses_.pop();

	AddToDiscoveredQueue_(startFromAddress);

	while (toProcessStartAddresses_.empty() == false)
	{
		address_ = toProcessStartAddresses_.front();
		toProcessStartAddresses_.pop();

		isEndOfBasicBlockFound_ = false;
		while (isEndOfBasicBlockFound_ == false)
		{
			auto operation = decoder.Decode(address_);
			if (operation == nullptr)
			{
				isEndOfBasicBlockFound_ = true;
			}
			else
			{
				int length = operation->GetMetadata().GetLengthInBytes();
				for (int i = 0; i < length; ++i)
					s_->m[address_ + (Address)i].isCode = true;

				auto outgoingEdges = operation->GetOutgoingEdges();
				outgoingEdges->Accept(*this);
			}
		}
	}

	for (auto traceAnchorAddress : discoveredTraceAnchorAddresses_)
	{
		simulatorEngine.CreateInterpretedTraceAnchor(traceAnchorAddress);
	}
}

void TraceCompilerFirstPass::Visit(UnconditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetJumpAddress());
	if (og.GetJumpAddress() < address_)
		discoveredTraceAnchorAddresses_.insert(og.GetJumpAddress());
}

void TraceCompilerFirstPass::Visit(ConditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetJumpNotTakenAddress());
	AddToDiscoveredQueue_(og.GetJumpTakenAddress());
	if (og.GetJumpTakenAddress() < address_)
		discoveredTraceAnchorAddresses_.insert(og.GetJumpTakenAddress());
}

void TraceCompilerFirstPass::Visit(UnconditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredQueue_(og.GetCallTakenAddress());
}

void TraceCompilerFirstPass::Visit(ConditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredQueue_(og.GetCallTakenAddress());
}

void TraceCompilerFirstPass::Visit(UnconditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void TraceCompilerFirstPass::Visit(ConditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetReturnNotTakenAddress());
}

void TraceCompilerFirstPass::Visit(NextOutgoingEdges & og)
{
	address_ = og.GetNextAddress();
}

void TraceCompilerFirstPass::Visit(NonCompilableOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetNonCompilableNextAddress());
}

void TraceCompilerFirstPass::Visit(NoneOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}
void TraceCompilerFirstPass::AddToDiscoveredQueue_(Address address)
{
	if (discoveredBlockStartAddresses_.find(address) == discoveredBlockStartAddresses_.end())
	{
		toProcessStartAddresses_.push(address);
		discoveredBlockStartAddresses_.insert(address);
	}
}
