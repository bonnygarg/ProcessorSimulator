#include "BlockCfgGenerator.h"

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


const int BlockCfgGenerator::MAX_NUMBER_OF_OPERATIONS_ = 100;

bool BlockCfgGenerator::CreateCfg(Decoder& decoder, Address startAddress, std::shared_ptr<Cfg> cfg)
{	
	cfg_ = cfg;
	cfg_->Clear();

	address_ = startAddress;
	isEndOfBasicBlockFound_ = false;
	numberOfOperations_ = 0;

	std::string key = MakeBasicBlockRecordKeyFromAddress_(startAddress);
	basicBlockRecord_ = std::make_shared<BasicBlockRecord>(key, startAddress);

	while (isEndOfBasicBlockFound_ == false)
	{
		auto operation = decoder.Decode(address_);
		if (!operation)
		{
			return false;
		}
		operation_ = std::shared_ptr<Operation>(std::move(operation));
		basicBlockRecord_->GetOperations().push_back(operation_);
		++numberOfOperations_;
		if (ShouldAbort_() == true)
		{
			return false;
		}
		auto outgoingEdges = operation_->GetOutgoingEdges();
		outgoingEdges->Accept(*this);
	}

	cfg_->GetBasicBlockRecords().insert(std::make_pair(key, basicBlockRecord_));
	cfg_->GetEntryBasicBlockRecords().push_back(basicBlockRecord_->GetKey());
	return true;
}

void BlockCfgGenerator::Visit(UnconditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCfgGenerator::Visit(ConditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCfgGenerator::Visit(UnconditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCfgGenerator::Visit(ConditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCfgGenerator::Visit(UnconditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCfgGenerator::Visit(ConditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

void BlockCfgGenerator::Visit(NextOutgoingEdges & og)
{
	address_ = og.GetNextAddress();
}

void BlockCfgGenerator::Visit(NonCompilableOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	
	std::string ncorKey = MakeNonCompilableOperationRecordKeyFromAddress_(address_);
	NonCompilableOperationRecord ncor(ncorKey, address_, operation_, "");
	cfg_->GetNonCompilableOperationRecords().insert(std::make_pair(ncorKey, ncor));

	basicBlockRecord_->SetResumeFromRecord(ncorKey);
}

void BlockCfgGenerator::Visit(NoneOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

std::string BlockCfgGenerator::MakeBasicBlockRecordKeyFromAddress_(Address address)
{
	std::ostringstream outstr;
	outstr << "bb" << address;
	return outstr.str();
}

std::string BlockCfgGenerator::MakeNonCompilableOperationRecordKeyFromAddress_(Address address)
{
	std::ostringstream outstr;
	outstr << "op" << address;
	return outstr.str();
}

bool BlockCfgGenerator::ShouldAbort_()
{
	return numberOfOperations_ > BlockCfgGenerator::MAX_NUMBER_OF_OPERATIONS_;
}
