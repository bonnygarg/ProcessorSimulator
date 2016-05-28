#include "OperationMetadata.h"

OperationMetadata::OperationMetadata(const std::string & functionName, bool canInterrupt, int lengthInBytes) :
	functionName_(functionName),
	canInterrupt_(canInterrupt),
	lengthInBytes_(lengthInBytes)
{}

std::string OperationMetadata::GetFunctionName() const
{
	return functionName_;
}

bool OperationMetadata::CanInterrupt() const
{
	return canInterrupt_;
}

int OperationMetadata::GetLengthInBytes() const
{
	return lengthInBytes_;
}
