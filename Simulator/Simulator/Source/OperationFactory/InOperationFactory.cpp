#include "InOperationFactory.h"

InOperationFactory::InOperationFactory(const OperationMetadata & metadata, const IoBridge& ioBridge) :
	OperationFactory(metadata),
	ioBridge_(ioBridge)
{
}

std::unique_ptr<Operation> InOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new InOperation(s, address, metadata_, ioBridge_));
}
