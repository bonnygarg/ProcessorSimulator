#ifndef _RESTART_OPERATION_FACTORY_H_
#define _RESTART_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\RestartOperations.h>

class RestartOperationFactory : public OperationFactory
{
public:
	RestartOperationFactory(const OperationMetadata& metadata, NoOperandProcessorFunction function, Address callAddress);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	NoOperandProcessorFunction function_;
	Address callAddress_;
};

#endif