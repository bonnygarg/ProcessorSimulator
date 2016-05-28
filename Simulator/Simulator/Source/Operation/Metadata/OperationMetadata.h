#ifndef _OPERATION_METADATA_H_
#define _OPERATION_METADATA_H_

#include <string>

class OperationMetadata
{
public:
	OperationMetadata(const std::string& functionName, bool canInterrupt, int lengthInBytes);
	std::string GetFunctionName() const;
	bool CanInterrupt() const;
	int GetLengthInBytes() const;
private:
	std::string functionName_;
	bool canInterrupt_;
	int lengthInBytes_;
};

#endif
