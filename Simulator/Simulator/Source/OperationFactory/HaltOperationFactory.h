#ifndef _HALT_OPERATION_FACTORY_H_
#define _HALT_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\HaltOperation.h>

class HaltOperationFactory : public OperationFactory
{
public:
	HaltOperationFactory(const OperationMetadata& metadata, NoOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	NoOperandProcessorFunction function_;
};

#endif