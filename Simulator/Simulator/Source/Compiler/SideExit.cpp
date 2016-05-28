#include "SideExit.h"

const int SideExit::EXECUTION_COUNT_THRESHOLD = 10;
const int SideExit::RECORD_ATTEMPT_COUNT_THRESHOLD = 2;

SideExit::SideExit(Address address, const std::string& basicBlockRecordKey) : 
	address_(address),
	basicBlockRecordKey_(basicBlockRecordKey),
	executionCount_(0),
	recordAttemptCount_(0)
{}

void SideExit::IncrementExecutionCount()
{
	++executionCount_;
}

void SideExit::IncrementRecordAttemptCount()
{
	++recordAttemptCount_;
}

bool SideExit::IsHot()
{
	return (executionCount_ > SideExit::EXECUTION_COUNT_THRESHOLD);
}

bool SideExit::IsRecordable()
{
	return (recordAttemptCount_ < SideExit::RECORD_ATTEMPT_COUNT_THRESHOLD);
}

const std::string & SideExit::GetBasicBlockRecordKey() const
{
	return basicBlockRecordKey_;
}
