#include "ConditionalReturnOperationFactory.h"

ConditionalReturnOperationFactory::ConditionalReturnOperationFactory(const OperationMetadata & metadata, NoOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> ConditionalReturnOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new ConditionalReturnOperation(s, address, metadata_, function_));
}
