#ifndef _BYTE_OPERAND_OPERATION_FACTORY_H_
#define _BYTE_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\ByteOperandOperation.h>

class ByteOperandOperationFactory : public OperationFactory
{
public:
	ByteOperandOperationFactory(const OperationMetadata& metadata, ByteOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	ByteOperandProcessorFunction function_;
};

#endif