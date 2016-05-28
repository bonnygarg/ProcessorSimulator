#ifndef _CONDITIONAL_JUMP_OPERAND_OPERATION_FACTORY_H_
#define _CONDITIONAL_JUMP_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\ConditionalJumpOperation.h>

class ConditionalJumpOperationFactory : public OperationFactory
{
public:
	ConditionalJumpOperationFactory(const OperationMetadata& metadata, WordOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	WordOperandProcessorFunction function_;
};

#endif