#include "UnconditionalReturnOperationFactory.h"

UnconditionalReturnOperationFactory::UnconditionalReturnOperationFactory(const OperationMetadata & metadata, NoOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> UnconditionalReturnOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new UnconditionalReturnOperation(s, address, metadata_, function_));
}
