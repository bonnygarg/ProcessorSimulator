#include "Cfg.h"

Cfg::Cfg(const std::string & key) :
	key_(key)
{
}

std::string Cfg::GetKey() const
{
	return key_;
}

const std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>>& Cfg::GetBasicBlockRecords() const
{
	return basicBlockRecords_;
}

std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>>& Cfg::GetBasicBlockRecords()
{
	return basicBlockRecords_;
}

void Cfg::SetBasicBlockRecords(const std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>>& basicBlockRecords)
{
	basicBlockRecords_ = basicBlockRecords;
}

const std::vector<std::string>& Cfg::GetEntryBasicBlockRecords() const
{
	return entryBasicBlockRecords_;
}

std::vector<std::string>& Cfg::GetEntryBasicBlockRecords()
{
	return entryBasicBlockRecords_;
}

void Cfg::SetEntryBasicBlockRecords(const std::vector<std::string>& entryBasicBlockRecords)
{
	entryBasicBlockRecords_ = entryBasicBlockRecords;
}

const std::unordered_map<std::string, NonCompilableOperationRecord>& Cfg::GetNonCompilableOperationRecords() const
{
	return nonCompilableOperationRecords_;
}

std::unordered_map<std::string, NonCompilableOperationRecord>& Cfg::GetNonCompilableOperationRecords()
{
	return nonCompilableOperationRecords_;
}

void Cfg::SetNonCompilableOperationRecords(const std::unordered_map<std::string, NonCompilableOperationRecord>& nonCompilableOperationRecords)
{
	nonCompilableOperationRecords_ = nonCompilableOperationRecords;
}

void Cfg::Clear()
{
	basicBlockRecords_.clear();
	entryBasicBlockRecords_.clear();
	nonCompilableOperationRecords_.clear();
}
