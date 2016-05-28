#ifndef _UNCONDTIONAL_CALL_OPERATION_FACTORY_H_
#define _UNCONDITIONAL_CALL_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\UnconditionalCallOperation.h>

class UnconditionalCallOperationFactory : public OperationFactory
{
public:
	UnconditionalCallOperationFactory(const OperationMetadata& metadata, WordOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	WordOperandProcessorFunction function_;
};

#endif