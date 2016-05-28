#include "HaltOperationFactory.h"

HaltOperationFactory::HaltOperationFactory(const OperationMetadata & metadata, NoOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> HaltOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new HaltOperation(s, address, metadata_, function_));
}
