#include "BlockCompilerFirstPass.h"

#include <SimulatorEngine\BlockCompiler\BlockCompilerSimulatorEngine.h>

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

BlockCompilerFirstPass::BlockCompilerFirstPass() : 
	isEndOfBasicBlockFound_(false),
	address_(0),
	simulationUnitTable_(nullptr)
{}

void BlockCompilerFirstPass::Perform(State* s, Address startFromAddress, Decoder& decoder, std::unordered_map<Address, std::shared_ptr<SimulationUnit>>* simulationUnitTable, BlockCompilerSimulatorEngine& simulatorEngine)
{
	s_ = s;
	simulationUnitTable_ = simulationUnitTable;

	discoveredStartAddresses_.clear();
	while (toProcessStartAddresses_.empty() == false)
		toProcessStartAddresses_.pop();

	AddToDiscoveredQueue_(startFromAddress);

	while (toProcessStartAddresses_.empty() == false)
	{
		address_ = toProcessStartAddresses_.front();
		toProcessStartAddresses_.pop();

		simulatorEngine.CreateInterpretedBlockStart(address_);
		
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
}

void BlockCompilerFirstPass::AddToDiscoveredQueue_(Address address)
{
	if (discoveredStartAddresses_.find(address) == discoveredStartAddresses_.end())
	{
		toProcessStartAddresses_.push(address);
		discoveredStartAddresses_.insert(address);
	}
}

void BlockCompilerFirstPass::Visit(UnconditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetJumpAddress());
}

void BlockCompilerFirstPass::Visit(ConditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetJumpNotTakenAddress());
	AddToDiscoveredQueue_(og.GetJumpTakenAddress());
}

void BlockCompilerFirstPass::Visit(UnconditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredQueue_(og.GetCallTakenAddress());
}

void BlockCompilerFirstPass::Visit(ConditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredQueue_(og.GetCallTakenAddress());
}

void BlockCompilerFirstPass::Visit(UnconditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCompilerFirstPass::Visit(ConditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetReturnNotTakenAddress());
}

void BlockCompilerFirstPass::Visit(NextOutgoingEdges & og)
{
	address_ = og.GetNextAddress();
}

void BlockCompilerFirstPass::Visit(NonCompilableOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredQueue_(og.GetNonCompilableNextAddress());
}

void BlockCompilerFirstPass::Visit(NoneOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}