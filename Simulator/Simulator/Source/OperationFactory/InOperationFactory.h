#ifndef _IN_OPERATION_FACTORY_H_
#define _IN_OPERATION_FACTORY_H_

#include <memory>
#include <IO\IoBridge.h>
#include "OperationFactory.h"
#include <Operation\InOperation.h>

class InOperationFactory : public OperationFactory
{
public:
	InOperationFactory(const OperationMetadata& metadata, const IoBridge& ioBridge);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	ByteOperandProcessorFunction function_;
	const IoBridge& ioBridge_;
};

#endif