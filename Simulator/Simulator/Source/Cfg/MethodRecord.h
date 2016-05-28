#ifndef _METHOD_RECORD_H_
#define _METHOD_RECORD_H_

#include <string>
#include <vector>
#include <memory>
#include <stack>

#include <Global\Global.h>
#include <Operation\Operation.h>

class MethodRecord
{
public:
	MethodRecord(const Address key);
	const Address GetKey() const;

	const Address GetStartAddress() const;
	void SetStartAddress(Address startAddress);

	const std::vector<std::string>& GetReturnToBasicBlockRecords() const;
	std::vector<std::string>& GetReturnToBasicBlockRecords();
	void SetReturnToBasicBlockRecords(const std::vector<std::string>& returnToBasicBlockRecords);

	const std::vector<std::string>& GetReturnFromBasicBlockRecords() const;
	std::vector<std::string>& GetReturnFromBasicBlockRecords();
	void SetReturnFromBasicBlockRecords(const std::vector<std::string>& returnFromBasicBlockRecords);

private:
	Address key_;
	Address startAddress_;
	std::vector<std::string> returnToBasicBlockRecords_;
	std::vector<std::string> returnFromBasicBlockRecords_;
};

#endif