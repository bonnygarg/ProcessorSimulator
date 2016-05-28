#include "MethodRecord.h"

MethodRecord::MethodRecord(const Address key) :
	key_(key)
{
}

const Address MethodRecord::GetKey() const
{
	return key_;
}


const Address MethodRecord::GetStartAddress() const
{
	return startAddress_;
}

void MethodRecord::SetStartAddress(Address startAddress)
{
	startAddress_ = startAddress;
}

const std::vector<std::string>& MethodRecord::GetReturnToBasicBlockRecords() const
{
	return returnToBasicBlockRecords_;
}

std::vector<std::string>& MethodRecord::GetReturnToBasicBlockRecords()
{
	return returnToBasicBlockRecords_;
}

void MethodRecord::SetReturnToBasicBlockRecords(const std::vector<std::string>& returnToBasicBlockRecords)
{
	returnToBasicBlockRecords_ = returnToBasicBlockRecords;
}

const std::vector<std::string>& MethodRecord::GetReturnFromBasicBlockRecords() const
{
	return returnFromBasicBlockRecords_;
}

std::vector<std::string>& MethodRecord::GetReturnFromBasicBlockRecords()
{
	return returnFromBasicBlockRecords_;
}

void MethodRecord::SetReturnFromBasicBlockRecords(const std::vector<std::string>& returnFromBasicBlockRecords)
{
	returnFromBasicBlockRecords_ = returnFromBasicBlockRecords;
}
