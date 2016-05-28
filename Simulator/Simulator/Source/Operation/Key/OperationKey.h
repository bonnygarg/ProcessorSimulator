#ifndef _OPERATION_KEY_H_
#define _OPERATION_KEY_H_

#include <Global\Global.h>
#include <State\State.h>

class OperationKey
{
	friend class OperationKeyHasher;
public:
	OperationKey(Byte opcode);
	bool operator<(const OperationKey& rhs) const
	{
		return (opcode_ < rhs.opcode_);
	}
	bool operator==(const OperationKey& rhs) const
	{
		return (opcode_ == rhs.opcode_);
	}
private:
	Byte opcode_;
};

#endif