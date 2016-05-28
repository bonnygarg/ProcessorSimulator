#ifndef _OPERATION_KEY_HASHER_H_
#define _OPERATION_KEY_HASHER_H_

#include <Global\Global.h>
#include "OperationKey.h"

class OperationKeyHasher
{
public:
	size_t operator()(const OperationKey& key) const
	{
		return (size_t)key.opcode_;
	}
};

#endif