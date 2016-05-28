#include "WordOperandOperationFactory.h"

WordOperandOperationFactory::WordOperandOperationFactory(const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> WordOperandOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new WordOperandOperation(s, address, metadata_, function_));
}
