#include "ByteOperandOperationFactory.h"

ByteOperandOperationFactory::ByteOperandOperationFactory(const OperationMetadata & metadata, ByteOperandProcessorFunction function) :
	OperationFactory(metadata),
	function_(function)
{
}

std::unique_ptr<Operation> ByteOperandOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new ByteOperandOperation(s, address, metadata_, function_));
}
