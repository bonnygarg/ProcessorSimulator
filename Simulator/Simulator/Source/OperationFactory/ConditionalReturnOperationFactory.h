#ifndef _CONDITIONAL_RETURN_OPERAND_OPERATION_FACTORY_H_
#define _CONDITIONAL_RETURN_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\ConditionalReturnOperation.h>

class ConditionalReturnOperationFactory : public OperationFactory
{
public:
	ConditionalReturnOperationFactory(const OperationMetadata& metadata, NoOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	NoOperandProcessorFunction function_;
};

#endif