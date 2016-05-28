#ifndef _NO_OPERAND_OPERATION_FACTORY_H_
#define _NO_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\NoOperandOperation.h>

class NoOperandOperationFactory : public OperationFactory
{
public:
	NoOperandOperationFactory(const OperationMetadata& metadata, NoOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	NoOperandProcessorFunction function_;
};

#endif