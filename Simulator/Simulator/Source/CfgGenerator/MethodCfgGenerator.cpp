#include "MethodCfgGenerator.h"

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

const int MethodCfgGenerator::MAX_NUMBER_OF_OPERATIONS_ = 1000;

bool MethodCfgGenerator::CreateCfg(Decoder & decoder, Address startAddress, std::shared_ptr<Cfg> cfg)
{
	cfg_ = cfg;
	cfg_->Clear();
	
	address_ = startAddress;
	while (toProcessMethodRecords_.empty() == false)
		toProcessMethodRecords_.pop();
	discoveredMethodRecords_.clear();
	numberOfOperations_ = 0;

	MethodRecord methodRecord(startAddress);
	methodRecord.SetStartAddress(startAddress);
	discoveredMethodRecords_.insert(std::make_pair(startAddress, methodRecord));
	toProcessMethodRecords_.push(startAddress);

	while (toProcessMethodRecords_.empty() == false)
	{
		Address currentMethodStartAddress = toProcessMethodRecords_.front();
		toProcessMethodRecords_.pop();

		currentMethodRecordIterator_ = discoveredMethodRecords_.find(currentMethodStartAddress);

		while (toProcessBasicBlockRecords_.empty() == false)
			toProcessBasicBlockRecords_.pop();
		discoveredBasicBlockRecords_.clear();
		AddToDiscoveredBasicBlockRecordQueue_(currentMethodStartAddress);
		
		while (toProcessBasicBlockRecords_.empty() == false)
		{
			address_ = toProcessBasicBlockRecords_.front();
			toProcessBasicBlockRecords_.pop();

			std::string key = MakeBasicBlockRecordKey_(currentMethodStartAddress, address_);
			currentBasicBlockRecord_ = std::make_shared<BasicBlockRecord>(key, address_);

			if (cfg_->GetBasicBlockRecords().empty() == true)
			{
				// first basic block record is also entry block
				cfg_->GetEntryBasicBlockRecords().push_back(currentBasicBlockRecord_->GetKey());
			}
			cfg_->GetBasicBlockRecords().insert(std::make_pair(currentBasicBlockRecord_->GetKey(), currentBasicBlockRecord_));

			isEndOfBasicBlockFound_ = false;
			while (isEndOfBasicBlockFound_ == false)
			{
				auto operation = decoder.Decode(address_);
				if (!operation)
					return false;
				operation_ = std::shared_ptr<Operation>(std::move(operation));
				currentBasicBlockRecord_->GetOperations().push_back(operation_);
				++numberOfOperations_;
				if (ShouldAbort_() == true)
					return false;
				auto outgoingEdges = operation_->GetOutgoingEdges();
				outgoingEdges->Accept(*this);
			}
		}

		for (auto returnFromBasicBlockRecordKey : currentMethodRecordIterator_->second.GetReturnFromBasicBlockRecords())
		{
			auto returnFromBasicBlockRecord = cfg_->GetBasicBlockRecords().find(returnFromBasicBlockRecordKey);
			for (auto returnToBasicBlockRecordKey : currentMethodRecordIterator_->second.GetReturnToBasicBlockRecords())
				returnFromBasicBlockRecord->second->GetOutgoingEdges().push_back(returnToBasicBlockRecordKey);
		}
	}

	return true;
}

void MethodCfgGenerator::Visit(UnconditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredBasicBlockRecordQueue_(og.GetJumpAddress());
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetJumpAddress()));
}

void MethodCfgGenerator::Visit(ConditionalJumpOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredBasicBlockRecordQueue_(og.GetJumpNotTakenAddress());
	AddToDiscoveredBasicBlockRecordQueue_(og.GetJumpTakenAddress());
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetJumpTakenAddress()));
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetJumpNotTakenAddress()));
}

void MethodCfgGenerator::Visit(UnconditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredBasicBlockRecordQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredMethodRecordQueue_(og.GetCallTakenAddress(), MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetCallNotTakenAddress()));
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(og.GetCallTakenAddress(), og.GetCallTakenAddress()));
}

void MethodCfgGenerator::Visit(ConditionalCallOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	AddToDiscoveredBasicBlockRecordQueue_(og.GetCallNotTakenAddress());
	AddToDiscoveredMethodRecordQueue_(og.GetCallTakenAddress(), MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetCallNotTakenAddress()));
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(og.GetCallTakenAddress(), og.GetCallTakenAddress()));
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetCallNotTakenAddress()));
}

void MethodCfgGenerator::Visit(UnconditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	currentMethodRecordIterator_->second.GetReturnFromBasicBlockRecords().push_back(currentBasicBlockRecord_->GetKey());
}

void MethodCfgGenerator::Visit(ConditionalReturnOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
	currentMethodRecordIterator_->second.GetReturnFromBasicBlockRecords().push_back(currentBasicBlockRecord_->GetKey());
	AddToDiscoveredBasicBlockRecordQueue_(og.GetReturnNotTakenAddress());
	currentBasicBlockRecord_->GetOutgoingEdges().push_back(MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetReturnNotTakenAddress()));
}

void MethodCfgGenerator::Visit(NextOutgoingEdges & og)
{
	address_ = og.GetNextAddress();
}

void MethodCfgGenerator::Visit(NonCompilableOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;

	std::string ncorKey = MakeNonCompilableOperationRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), currentBasicBlockRecord_->GetStartAddress(), address_);
	std::string ncorResumeRecordKey = MakeBasicBlockRecordKey_(currentMethodRecordIterator_->second.GetStartAddress(), og.GetNonCompilableNextAddress());
	auto ncor = NonCompilableOperationRecord(ncorKey, address_, operation_, ncorResumeRecordKey);

	currentBasicBlockRecord_->SetResumeFromRecord(ncorKey);

	cfg_->GetNonCompilableOperationRecords().insert(std::make_pair(ncorKey, ncor));
	cfg_->GetEntryBasicBlockRecords().push_back(ncorResumeRecordKey);
	
	AddToDiscoveredBasicBlockRecordQueue_(og.GetNonCompilableNextAddress());
}

void MethodCfgGenerator::Visit(NoneOutgoingEdges & og)
{
	isEndOfBasicBlockFound_ = true;
}

std::string MethodCfgGenerator::MakeBasicBlockRecordKey_(Address methodStartAddress, Address blockStartAddress)
{
	std::ostringstream outstr;
	outstr << "fn" << methodStartAddress <<  "bb" << blockStartAddress;
	return outstr.str();
}

std::string MethodCfgGenerator::MakeNonCompilableOperationRecordKey_(Address methodStartAddress, Address blockStartAddress, Address operationAddress)
{
	std::ostringstream outstr;
	outstr << "fn" << methodStartAddress << "bb" << blockStartAddress << "op" << operationAddress;
	return outstr.str();
}

bool MethodCfgGenerator::ShouldAbort_()
{
	return (numberOfOperations_ > MethodCfgGenerator::MAX_NUMBER_OF_OPERATIONS_);
}

void MethodCfgGenerator::AddToDiscoveredBasicBlockRecordQueue_(Address address)
{
	if (discoveredBasicBlockRecords_.find(address) == discoveredBasicBlockRecords_.end())
	{
		discoveredBasicBlockRecords_.insert(address);
		toProcessBasicBlockRecords_.push(address);
	}
}

void MethodCfgGenerator::AddToDiscoveredMethodRecordQueue_(Address startAddress, std::string returnToBasicBlockRecord)
{
	auto methodRecordIterator = discoveredMethodRecords_.find(startAddress);
	if (methodRecordIterator == discoveredMethodRecords_.end())
	{
		MethodRecord methodRecord(startAddress);
		methodRecord.SetStartAddress(startAddress);
		methodRecord.GetReturnToBasicBlockRecords().push_back(returnToBasicBlockRecord);

		discoveredMethodRecords_.insert(std::make_pair(startAddress, methodRecord));
		toProcessMethodRecords_.push(startAddress);
	}
	else
	{
		for (auto existingReturnToBasicBlockRecordKey : methodRecordIterator->second.GetReturnToBasicBlockRecords())
		{
			if (existingReturnToBasicBlockRecordKey == returnToBasicBlockRecord)
			{
				return;
			}
		}
		methodRecordIterator->second.GetReturnToBasicBlockRecords().push_back(returnToBasicBlockRecord);
	}
}
