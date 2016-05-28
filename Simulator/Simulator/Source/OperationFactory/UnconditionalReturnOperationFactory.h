#ifndef _UNCONDITIONAL_RETURN_OPERAND_OPERATION_FACTORY_H_
#define _UNCONDITIONAL_RETURN_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\UnconditionalReturnOperation.h>

class UnconditionalReturnOperationFactory : public OperationFactory
{
public:
	UnconditionalReturnOperationFactory(const OperationMetadata& metadata, NoOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	NoOperandProcessorFunction function_;
};

#endif