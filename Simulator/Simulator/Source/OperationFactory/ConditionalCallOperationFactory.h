#ifndef _CONDITIONAL_CALL_OPERAND_OPERATION_FACTORY_H_
#define _CONDITIONAL_CALL_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\ConditionalCallOperation.h>

class ConditionalCallOperationFactory : public OperationFactory
{
public:
	ConditionalCallOperationFactory(const OperationMetadata& metadata, WordOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	WordOperandProcessorFunction function_;
};

#endif