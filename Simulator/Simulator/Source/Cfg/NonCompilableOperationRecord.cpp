#include "NonCompilableOperationRecord.h"

NonCompilableOperationRecord::NonCompilableOperationRecord(const std::string & key, Address address, std::shared_ptr<Operation> operation, const std::string & resumeFromRecord) :
	key_(key),
	address_(address),
	operation_(operation),
	resumeFromRecord_(resumeFromRecord)
{}

const std::string & NonCompilableOperationRecord::GetKey() const
{
	return key_;
}

const Address NonCompilableOperationRecord::GetAddress() const
{
	return address_;
}

const std::shared_ptr<Operation> NonCompilableOperationRecord::GetOperation() const
{
	return operation_;
}

std::shared_ptr<Operation> NonCompilableOperationRecord::GetOperation()
{
	return operation_;
}

const std::string & NonCompilableOperationRecord::GetResumeFromRecord() const
{
	return resumeFromRecord_;
}

