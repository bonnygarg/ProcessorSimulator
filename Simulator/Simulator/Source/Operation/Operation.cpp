#include "Operation.h"

Operation::Operation(State * s, Address address, const OperationMetadata & metadata) :
	s_(s),
	address_(address),
	metadata_(metadata)
{}

const OperationMetadata & Operation::GetMetadata()
{
	return metadata_;
}
