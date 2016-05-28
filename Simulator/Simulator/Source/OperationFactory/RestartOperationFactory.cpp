#include "RestartOperationFactory.h"

RestartOperationFactory::RestartOperationFactory(const OperationMetadata & metadata, NoOperandProcessorFunction function, Address callAddress) :
	OperationFactory(metadata),
	function_(function),
	callAddress_(callAddress)
{
}

std::unique_ptr<Operation> RestartOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new RestartOperation(s, address, metadata_, function_, callAddress_));
}
