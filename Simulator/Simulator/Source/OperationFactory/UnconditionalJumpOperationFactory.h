#ifndef _UNCONDTIONAL_JUMP_OPERATION_FACTORY_H_
#define _UNCONDITIONAL_JUMP_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\UnconditionalJumpOperation.h>

class UnconditionalJumpOperationFactory : public OperationFactory
{
public:
	UnconditionalJumpOperationFactory(const OperationMetadata& metadata, WordOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	WordOperandProcessorFunction function_;
};

#endif