#include "NoOperandOperationFactory.h"

NoOperandOperationFactory::NoOperandOperationFactory(const OperationMetadata & metadata, NoOperandProcessorFunction function) : 
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> NoOperandOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new NoOperandOperation(s, address, metadata_, function_));
}
