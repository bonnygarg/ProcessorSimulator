#include "ConditionalJumpOperationFactory.h"

ConditionalJumpOperationFactory::ConditionalJumpOperationFactory(const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> ConditionalJumpOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new ConditionalJumpOperation(s, address, metadata_, function_));
}
