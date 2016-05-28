#ifndef _OPERATION_FACTORY_H_
#define _OPERATION_FACTORY_H_

#include <Global\Global.h>
#include <Operation\Operation.h>
#include <Operation\Metadata\OperationMetadata.h>
#include <State\State.h>
#include <memory>

class OperationFactory
{
public:
	OperationFactory(const OperationMetadata& metadata);
	virtual std::unique_ptr<Operation> CreateOperation(State* s, Address address) = 0;
protected:
	OperationMetadata metadata_;
};

#endif