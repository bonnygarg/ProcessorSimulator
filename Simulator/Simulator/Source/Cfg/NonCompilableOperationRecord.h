#ifndef _NON_COMPILABLE_OPERATION_H_
#define _NON_COMPILABLE_OPERATION_H_

#include <memory>
#include <string>

#include <Global\Global.h>
#include <Operation\Operation.h>

class NonCompilableOperationRecord
{
public:
	NonCompilableOperationRecord(const std::string& key, Address address, std::shared_ptr<Operation> operation, const std::string& resumeFromRecord);

	const std::string& GetKey() const;

	const Address GetAddress() const;
	
	const std::shared_ptr<Operation> GetOperation() const;
	std::shared_ptr<Operation> GetOperation();
	
	const std::string& GetResumeFromRecord() const;
	
private:
	std::string key_;
	Address address_;
	std::shared_ptr<Operation> operation_;
	std::string resumeFromRecord_;
};

#endif