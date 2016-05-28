#include "UnconditionalJumpOperationFactory.h"

UnconditionalJumpOperationFactory::UnconditionalJumpOperationFactory(const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> UnconditionalJumpOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new UnconditionalJumpOperation(s, address, metadata_, function_));
}
