#ifndef _RECORDED_OPERATION_H_
#define _RECORDED_OPERATION_H_

#include <memory>

#include <Global\Global.h>
#include <Operation\Operation.h>

class RecordedOperation
{
public:
	RecordedOperation(Address address, std::shared_ptr<Operation> operation);
	const Address GetAddress() const;
	std::shared_ptr<Operation> GetOperation() const;
private:
	Address address_;
	std::shared_ptr<Operation> operation_;
};

#endif