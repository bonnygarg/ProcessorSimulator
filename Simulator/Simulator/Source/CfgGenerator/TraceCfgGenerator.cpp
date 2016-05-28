#include "TraceCfgGenerator.h"

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

const std::string TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY = "anchor";

bool TraceCfgGenerator::CreateCfg(const std::vector<RecordedOperation>& recordedOperations, std::shared_ptr<Cfg> cfg)
{
	cfg_ = cfg;
	cfg_->Clear();

	if (recordedOperations.size() < 1)
		return false;

	shouldAbort_ = false;
	recordCount_ = 0;
	recordedOperations_ = &recordedOperations;
	recordedOperationsIndex_ = 0;
	anchorAddress_ = (*recordedOperations_)[0].GetAddress();
	std::string key = TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY;
	currentBasicBlockRecord_ = std::make_shared<BasicBlockRecord>(key, anchorAddress_);

	cfg_->GetBasicBlockRecords().insert(std::make_pair(key, currentBasicBlockRecord_));
	cfg_->GetEntryBasicBlockRecords().push_back(key);

	while (recordedOperationsIndex_ < recordedOperations_->size())
	{
		operation_ = (*recordedOperations_)[recordedOperationsIndex_].GetOperation();
		if (!operation_)
			return false;
		currentBasicBlockRecord_->GetOperations().push_back(operation_);
		auto outgoingEdges = operation_->GetOutgoingEdges();
		outgoingEdges->Accept(*this);
		if (shouldAbort_ == true)
			return false;
		++recordedOperationsIndex_;
	}
	
	return true;
}

bool TraceCfgGenerator::ExtendCfg(const std::vector<RecordedOperation>& recordedOperations, std::shared_ptr<Cfg> cfg, std::string sideExitBasicBlockRecordKey, Address anchorAddress, int recordCount)
{
	cfg_ = std::make_shared<Cfg>(cfg->GetKey());
	cfg_->Clear();

	if (recordedOperations.size() < 1)
		return false;

	shouldAbort_ = false;
	recordCount_ = recordCount;
	recordedOperations_ = &recordedOperations;
	recordedOperationsIndex_ = 0;
	anchorAddress_ = anchorAddress;
	std::shared_ptr<BasicBlockRecord> sideExitBasicBlockRecord = cfg->GetBasicBlockRecords().find(sideExitBasicBlockRecordKey)->second;
	currentBasicBlockRecord_ = std::make_shared<BasicBlockRecord>(sideExitBasicBlockRecordKey, sideExitBasicBlockRecord->GetStartAddress());
	currentBasicBlockRecord_->SetCallStack(sideExitBasicBlockRecord->GetCallStack());

	cfg_->GetBasicBlockRecords().insert(std::make_pair(sideExitBasicBlockRecordKey, currentBasicBlockRecord_));

	while (recordedOperationsIndex_ < recordedOperations_->size())
	{
		operation_ = (*recordedOperations_)[recordedOperationsIndex_].GetOperation();
		if (!operation_)
			return false;
		currentBasicBlockRecord_->GetOperations().push_back(operation_);
		auto outgoingEdges = operation_->GetOutgoingEdges();
		outgoingEdges->Accept(*this);
		if (shouldAbort_ == true)
			return false;
		++recordedOperationsIndex_;
	}

	cfg->GetBasicBlockRecords().erase(sideExitBasicBlockRecordKey);
	cfg->GetBasicBlockRecords().insert(cfg_->GetBasicBlockRecords().begin(), cfg_->GetBasicBlockRecords().end());
	for (auto entryBasicBlockRecord : cfg_->GetEntryBasicBlockRecords())
		cfg->GetEntryBasicBlockRecords().push_back(entryBasicBlockRecord);
	cfg->GetNonCompilableOperationRecords().insert(cfg_->GetNonCompilableOperationRecords().begin(), cfg_->GetNonCompilableOperationRecords().end());

	return true;
}

void TraceCfgGenerator::Visit(UnconditionalJumpOutgoingEdges & og)
{
	std::shared_ptr<BasicBlockRecord> newBasicBlockRecord;
	if (og.GetJumpAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		std::string newBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, currentBasicBlockRecord_->GetCallStack(), currentBasicBlockRecord_->GetStartAddress(), og.GetJumpAddress());
		if (cfg_->GetBasicBlockRecords().find(newBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		newBasicBlockRecord = std::make_shared<BasicBlockRecord>(newBasicBlockRecordKey, og.GetJumpAddress());
		newBasicBlockRecord->SetCallStack(currentBasicBlockRecord_->GetCallStack());
		cfg_->GetBasicBlockRecords().insert(std::make_pair(newBasicBlockRecordKey, newBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(newBasicBlockRecordKey);
	}
	currentBasicBlockRecord_ = newBasicBlockRecord;
}

void TraceCfgGenerator::Visit(ConditionalJumpOutgoingEdges & og)
{
	std::shared_ptr<BasicBlockRecord> takenBasicBlockRecord;
	if (og.GetJumpTakenAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		std::string takenBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, currentBasicBlockRecord_->GetCallStack(), currentBasicBlockRecord_->GetStartAddress(), og.GetJumpTakenAddress());
		if (cfg_->GetBasicBlockRecords().find(takenBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		takenBasicBlockRecord = std::make_shared<BasicBlockRecord>(takenBasicBlockRecordKey, og.GetJumpTakenAddress());
		takenBasicBlockRecord->SetCallStack(currentBasicBlockRecord_->GetCallStack());
		cfg_->GetBasicBlockRecords().insert(std::make_pair(takenBasicBlockRecordKey, takenBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(takenBasicBlockRecordKey);
	}

	std::shared_ptr<BasicBlockRecord> notTakenBasicBlockRecord;
	if (og.GetJumpNotTakenAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		std::string notTakenBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, currentBasicBlockRecord_->GetCallStack(), currentBasicBlockRecord_->GetStartAddress(), og.GetJumpNotTakenAddress());
		if (cfg_->GetBasicBlockRecords().find(notTakenBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		notTakenBasicBlockRecord = std::make_shared<BasicBlockRecord>(notTakenBasicBlockRecordKey, og.GetJumpNotTakenAddress());
		notTakenBasicBlockRecord->SetCallStack(currentBasicBlockRecord_->GetCallStack());
		cfg_->GetBasicBlockRecords().insert(std::make_pair(notTakenBasicBlockRecordKey, notTakenBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(notTakenBasicBlockRecordKey);
	}

	if ((recordedOperationsIndex_ + 1) < recordedOperations_->size())
	{
		Address nextAddress = (*recordedOperations_)[recordedOperationsIndex_ + 1].GetAddress();
		if (nextAddress == og.GetJumpTakenAddress())
			currentBasicBlockRecord_ = takenBasicBlockRecord;
		else
			currentBasicBlockRecord_ = notTakenBasicBlockRecord;
	}
}

void TraceCfgGenerator::Visit(UnconditionalCallOutgoingEdges & og)
{
	std::shared_ptr<BasicBlockRecord> newBasicBlockRecord;
	if (og.GetCallTakenAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		if (IsRecursiveCall_(currentBasicBlockRecord_->GetCallStack(), og.GetCallNotTakenAddress()) == true)
		{
			shouldAbort_ = true;
			return;
		}
		auto newCallStack = currentBasicBlockRecord_->GetCallStack();
		newCallStack.push_front(og.GetCallNotTakenAddress());
		std::string newBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, newCallStack, currentBasicBlockRecord_->GetStartAddress(), og.GetCallTakenAddress());
		if (cfg_->GetBasicBlockRecords().find(newBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		newBasicBlockRecord = std::make_shared<BasicBlockRecord>(newBasicBlockRecordKey, og.GetCallTakenAddress());
		newBasicBlockRecord->SetCallStack(newCallStack);
		cfg_->GetBasicBlockRecords().insert(std::make_pair(newBasicBlockRecordKey, newBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(newBasicBlockRecordKey);
	}
	currentBasicBlockRecord_ = newBasicBlockRecord;
}

void TraceCfgGenerator::Visit(ConditionalCallOutgoingEdges & og)
{
	std::shared_ptr<BasicBlockRecord> takenBasicBlockRecord;
	if (og.GetCallTakenAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		if (IsRecursiveCall_(currentBasicBlockRecord_->GetCallStack(), og.GetCallNotTakenAddress()) == true)
		{
			shouldAbort_ = true;
			return;
		}
		auto newCallStack = currentBasicBlockRecord_->GetCallStack();
		newCallStack.push_front(og.GetCallNotTakenAddress());
		std::string takenBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, newCallStack, currentBasicBlockRecord_->GetStartAddress(), og.GetCallTakenAddress());
		if (cfg_->GetBasicBlockRecords().find(takenBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		takenBasicBlockRecord = std::make_shared<BasicBlockRecord>(takenBasicBlockRecordKey, og.GetCallTakenAddress());
		takenBasicBlockRecord->SetCallStack(newCallStack);
		cfg_->GetBasicBlockRecords().insert(std::make_pair(takenBasicBlockRecordKey, takenBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(takenBasicBlockRecordKey);
	}

	std::shared_ptr<BasicBlockRecord> notTakenBasicBlockRecord;
	if (og.GetCallNotTakenAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		std::string notTakenBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, currentBasicBlockRecord_->GetCallStack(), currentBasicBlockRecord_->GetStartAddress(), og.GetCallNotTakenAddress());
		if (cfg_->GetBasicBlockRecords().find(notTakenBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		notTakenBasicBlockRecord = std::make_shared<BasicBlockRecord>(notTakenBasicBlockRecordKey, og.GetCallNotTakenAddress());
		notTakenBasicBlockRecord->SetCallStack(currentBasicBlockRecord_->GetCallStack());
		cfg_->GetBasicBlockRecords().insert(std::make_pair(notTakenBasicBlockRecordKey, notTakenBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(notTakenBasicBlockRecordKey);
	}

	if ((recordedOperationsIndex_ + 1) < recordedOperations_->size())
	{
		Address nextAddress = (*recordedOperations_)[recordedOperationsIndex_ + 1].GetAddress();
		if (nextAddress == og.GetCallTakenAddress())
			currentBasicBlockRecord_ = takenBasicBlockRecord;
		else
			currentBasicBlockRecord_ = notTakenBasicBlockRecord;
	}
}

void TraceCfgGenerator::Visit(UnconditionalReturnOutgoingEdges & og)
{
	auto newCallStack = currentBasicBlockRecord_->GetCallStack();
	if (newCallStack.empty() == true)
	{
		shouldAbort_ = true;
		return;
	}
	Address returnToAddress = newCallStack.front();
	
	std::shared_ptr<BasicBlockRecord> newBasicBlockRecord;
	if (returnToAddress == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		newCallStack.pop_front();
		std::string newBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, newCallStack, currentBasicBlockRecord_->GetStartAddress(), returnToAddress);
		if (cfg_->GetBasicBlockRecords().find(newBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		newBasicBlockRecord = std::make_shared<BasicBlockRecord>(newBasicBlockRecordKey, returnToAddress);
		newBasicBlockRecord->SetCallStack(newCallStack);
		cfg_->GetBasicBlockRecords().insert(std::make_pair(newBasicBlockRecordKey, newBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(newBasicBlockRecordKey);
	}
	currentBasicBlockRecord_ = newBasicBlockRecord;
}

void TraceCfgGenerator::Visit(ConditionalReturnOutgoingEdges & og)
{
	auto newCallStack = currentBasicBlockRecord_->GetCallStack();
	if (newCallStack.empty() == true)
	{
		shouldAbort_ = true;
		return;
	}
	Address returnToAddress = newCallStack.front();

	std::shared_ptr<BasicBlockRecord> takenBasicBlockRecord;
	if (returnToAddress == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		std::string takenBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, newCallStack, currentBasicBlockRecord_->GetStartAddress(), returnToAddress);
		if (cfg_->GetBasicBlockRecords().find(takenBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		takenBasicBlockRecord = std::make_shared<BasicBlockRecord>(takenBasicBlockRecordKey, returnToAddress);
		takenBasicBlockRecord->SetCallStack(newCallStack);
		cfg_->GetBasicBlockRecords().insert(std::make_pair(takenBasicBlockRecordKey, takenBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(takenBasicBlockRecordKey);
	}

	std::shared_ptr<BasicBlockRecord> notTakenBasicBlockRecord;
	if (og.GetReturnNotTakenAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
	}
	else
	{
		std::string notTakenBasicBlockRecordKey = MakeBasicBlockRecordKey_(recordCount_, currentBasicBlockRecord_->GetCallStack(), currentBasicBlockRecord_->GetStartAddress(), og.GetReturnNotTakenAddress());
		if (cfg_->GetBasicBlockRecords().find(notTakenBasicBlockRecordKey) != cfg_->GetBasicBlockRecords().end())
		{
			shouldAbort_ = true;
			return;
		}
		notTakenBasicBlockRecord = std::make_shared<BasicBlockRecord>(notTakenBasicBlockRecordKey, og.GetReturnNotTakenAddress());
		notTakenBasicBlockRecord->SetCallStack(currentBasicBlockRecord_->GetCallStack());
		cfg_->GetBasicBlockRecords().insert(std::make_pair(notTakenBasicBlockRecordKey, notTakenBasicBlockRecord));

		currentBasicBlockRecord_->GetOutgoingEdges().push_back(notTakenBasicBlockRecordKey);
	}

	if ((recordedOperationsIndex_ + 1) < recordedOperations_->size())
	{
		Address nextAddress = (*recordedOperations_)[recordedOperationsIndex_ + 1].GetAddress();
		if (nextAddress == returnToAddress)
			currentBasicBlockRecord_ = takenBasicBlockRecord;
		else
			currentBasicBlockRecord_ = notTakenBasicBlockRecord;
	}
}

void TraceCfgGenerator::Visit(NextOutgoingEdges & og)
{
	// A--next edge-->anchor------>B----->(D)
	// ^                           |
	// |                           |
	// -----------------------------
	if (og.GetNextAddress() == anchorAddress_)
	{
		currentBasicBlockRecord_->GetOutgoingEdges().push_back(TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY);
		currentBasicBlockRecord_.reset();
	}
}

void TraceCfgGenerator::Visit(NonCompilableOutgoingEdges & og)
{
	Address ncorAddress = (*recordedOperations_)[recordedOperationsIndex_].GetAddress();
	std::string ncorKey = MakeNonCompilableOperationRecordKey_(currentBasicBlockRecord_->GetKey(), ncorAddress);
	
	std::string ncorResumeRecordKey;
	std::shared_ptr<BasicBlockRecord> newBasicBlockRecord;
	if (og.GetNonCompilableNextAddress() == anchorAddress_)
	{
		ncorResumeRecordKey = TraceCfgGenerator::ANCHOR_BASIC_BLOCK_RECORD_KEY;
	}
	else
	{
		ncorResumeRecordKey = MakeBasicBlockRecordKey_(recordCount_, currentBasicBlockRecord_->GetCallStack(), currentBasicBlockRecord_->GetStartAddress(), og.GetNonCompilableNextAddress());
		newBasicBlockRecord = std::make_shared<BasicBlockRecord>(ncorResumeRecordKey, og.GetNonCompilableNextAddress());
		cfg_->GetBasicBlockRecords().insert(std::make_pair(ncorResumeRecordKey, newBasicBlockRecord));

		cfg_->GetEntryBasicBlockRecords().push_back(ncorResumeRecordKey);
	}
	
	auto ncor = NonCompilableOperationRecord(ncorKey, ncorAddress, operation_, ncorResumeRecordKey);

	currentBasicBlockRecord_->SetResumeFromRecord(ncorKey);

	cfg_->GetNonCompilableOperationRecords().insert(std::make_pair(ncorKey, ncor));

	currentBasicBlockRecord_ = newBasicBlockRecord;
}

void TraceCfgGenerator::Visit(NoneOutgoingEdges & og)
{
	shouldAbort_ = true;
}

std::string TraceCfgGenerator::MakeBasicBlockRecordKey_(int recordCount, const std::list<Address>& callStack, Address parentBasicBlockRecordStartAddress, Address basicBlockRecordStartAddress)
{
	std::ostringstream outstr;
	outstr << "rc" << recordCount;
	for (auto returnAddress : callStack)
		outstr << "cs" << returnAddress;
	outstr << "pr" << parentBasicBlockRecordStartAddress;
	outstr << "bb" << basicBlockRecordStartAddress;
	return outstr.str();
}

std::string TraceCfgGenerator::MakeNonCompilableOperationRecordKey_(std::string basicBlockRecordKey, Address operationAddress)
{
	std::ostringstream outstr;
	outstr << basicBlockRecordKey;
	outstr << "op" << operationAddress;
	return outstr.str();
}

bool TraceCfgGenerator::IsRecursiveCall_(const std::list<Address> callStack, Address newReturnAddress)
{
	for (auto returnAddress : callStack)
	{
		if (returnAddress == newReturnAddress)
			return true;
	}
	return false;
}
