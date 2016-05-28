#ifndef _BASIC_BLOCK_RECORD_H_
#define _BASIC_BLOCK_RECORD_H_

#include <string>
#include <vector>
#include <memory>
#include <list>

#include <Global\Global.h>
#include <Operation\Operation.h>

class BasicBlockRecord
{
public:
	BasicBlockRecord(const std::string& key, Address startAddress);
	
	const std::string& GetKey() const;
	
	const Address GetStartAddress() const;
	
	const Address GetEndAddress() const;
	void SetEndAddress(Address endAddress);

	const std::vector<std::shared_ptr<Operation>>& GetOperations() const;
	std::vector<std::shared_ptr<Operation>>& GetOperations();
	void SetOperations(const std::vector<std::shared_ptr<Operation>>& operations);

	const std::vector<std::string>& GetOutgoingEdges() const;
	std::vector<std::string>& GetOutgoingEdges();
	void SetOutgoingEdges(const std::vector<std::string>& outgoingEdges);

	const std::list<Address>& GetCallStack() const;
	std::list<Address>& GetCallStack();
	void SetCallStack(const std::list<Address>& callStack);

	const std::string& GetResumeFromRecord() const;
	std::string& GetResumeFromRecord();
	void SetResumeFromRecord(const std::string& resumeFromRecord);

private:
	std::string key_;
	Address startAddress_;
	Address endAddress_;
	std::vector<std::shared_ptr<Operation>> operations_;
	std::vector<std::string> outgoingEdges_;
	std::list<Address> callStack_;
	std::string resumeFromRecord_;
};

#endif