#include "UnconditionalCallOperationFactory.h"

UnconditionalCallOperationFactory::UnconditionalCallOperationFactory(const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> UnconditionalCallOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new UnconditionalCallOperation(s, address, metadata_, function_));
}
