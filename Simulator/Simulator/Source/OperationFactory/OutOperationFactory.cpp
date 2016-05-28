#include "OutOperationFactory.h"

OutOperationFactory::OutOperationFactory(const OperationMetadata & metadata, const IoBridge& ioBridge) :
	OperationFactory(metadata),
	ioBridge_(ioBridge)
{
}

std::unique_ptr<Operation> OutOperationFactory::CreateOperation(State * s, Address address)
{
	return std::unique_ptr<Operation>(new OutOperation(s, address, metadata_, ioBridge_));
}
