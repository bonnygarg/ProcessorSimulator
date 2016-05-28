#include "MethodCompilerFirstPass.h"

#include <SimulatorEngine\MethodCompiler\MethodCompilerSimulatorEngine.h>

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


MethodCompilerFirstPass::MethodCompilerFirstPass() :
	isEndOfBasicBlockFound_(false),
	address_(0),
	simulationUnitTable_(nullptr)
{}

void MethodCompilerFirstPass::Perform(State * s, Address startFromAddress, Decoder & decoder, std::unordered_map<Address, std::shared_ptr<SimulationUnit>>* simulationUnitTable, MethodCompilerSimulatorEngine & simulatorEngine)
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

	for (auto methodStartAddress : discoveredMethodStartAddresses_)
	{
		simulatorEngine.CreateInterpretedMethodStart(methodStartAddress);
	}
}

void MethodCompilerFirstPass::Visit(UnconditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetJumpAddress());
}

void MethodCompilerFirstPass::Visit(ConditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetJumpNotTakenAddress());
	AddToDiscoveredQueue_(og.GetJumpTakenAddress());
}

void MethodCompilerFirstPass::Visit(UnconditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredQueue_(og.GetCallTakenAddress());
	discoveredMethodStartAddresses_.insert(og.GetCallTakenAddress());
}

void MethodCompilerFirstPass::Visit(ConditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredQueue_(og.GetCallTakenAddress());
	discoveredMethodStartAddresses_.insert(og.GetCallTakenAddress());
}

void MethodCompilerFirstPass::Visit(UnconditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void MethodCompilerFirstPass::Visit(ConditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetReturnNotTakenAddress());
}

void MethodCompilerFirstPass::Visit(NextOutgoingEdges & og)
{
	address_ = og.GetNextAddress();
}

void MethodCompilerFirstPass::Visit(NonCompilableOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetNonCompilableNextAddress());
}

void MethodCompilerFirstPass::Visit(NoneOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}
void MethodCompilerFirstPass::AddToDiscoveredQueue_(Address address)
{
	if (discoveredBlockStartAddresses_.find(address) == discoveredBlockStartAddresses_.end())
	{
		toProcessStartAddresses_.push(address);
		discoveredBlockStartAddresses_.insert(address);
	}
}
