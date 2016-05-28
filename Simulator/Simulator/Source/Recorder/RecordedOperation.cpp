#include "RecordedOperation.h"

RecordedOperation::RecordedOperation(Address address, std::shared_ptr<Operation> operation) :
	address_(address),
	operation_(operation)
{}

const Address RecordedOperation::GetAddress() const
{
	return address_;
}

std::shared_ptr<Operation> RecordedOperation::GetOperation() const
{
	return operation_;
}
