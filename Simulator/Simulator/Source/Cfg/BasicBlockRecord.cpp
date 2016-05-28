#include "BasicBlockRecord.h"

BasicBlockRecord::BasicBlockRecord(const std::string & key, Address startAddress) :
	key_(key),
	startAddress_(startAddress),
	endAddress_(0),
	resumeFromRecord_("")
{
}

const std::string& BasicBlockRecord::GetKey() const
{
	return key_;
}

const Address BasicBlockRecord::GetStartAddress() const
{
	return startAddress_;
}

const Address BasicBlockRecord::GetEndAddress() const
{
	return endAddress_;
}

void BasicBlockRecord::SetEndAddress(Address endAddress)
{
	endAddress_ = endAddress;
}

const std::vector<std::shared_ptr<Operation>>& BasicBlockRecord::GetOperations() const
{
	return operations_;
}

std::vector<std::shared_ptr<Operation>>& BasicBlockRecord::GetOperations()
{
	return operations_;
}

void BasicBlockRecord::SetOperations(const std::vector<std::shared_ptr<Operation>>& operations)
{
	operations_ = operations;
}

const std::vector<std::string>& BasicBlockRecord::GetOutgoingEdges() const
{
	return outgoingEdges_;
}

std::vector<std::string>& BasicBlockRecord::GetOutgoingEdges()
{
	return outgoingEdges_;
}

void BasicBlockRecord::SetOutgoingEdges(const std::vector<std::string>& outgoingEdges)
{
	outgoingEdges_ = outgoingEdges;
}

const std::list<Address>& BasicBlockRecord::GetCallStack() const
{
	return callStack_;
}

std::list<Address>& BasicBlockRecord::GetCallStack()
{
	return callStack_;
}

void BasicBlockRecord::SetCallStack(const std::list<Address>& callStack)
{
	callStack_ = callStack;
}

const std::string & BasicBlockRecord::GetResumeFromRecord() const
{
	return resumeFromRecord_;
}

std::string & BasicBlockRecord::GetResumeFromRecord()
{
	return resumeFromRecord_;
}

void BasicBlockRecord::SetResumeFromRecord(const std::string & resumeFromRecord)
{
	resumeFromRecord_ = resumeFromRecord;
}
