#include "ConditionalCallOperationFactory.h"

ConditionalCallOperationFactory::ConditionalCallOperationFactory(const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> ConditionalCallOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new ConditionalCallOperation(s, address, metadata_, function_));
}
