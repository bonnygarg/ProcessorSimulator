#ifndef _SIDE_EXIT_H_
#define _SIDE_EXIT_H_

#include <string>

#include <Global\Global.h>

class SideExit
{
public:
	SideExit(Address address, const std::string& basicBlockRecordKey);
	void IncrementExecutionCount();
	void IncrementRecordAttemptCount();
	bool IsHot();
	bool IsRecordable();
	const std::string& GetBasicBlockRecordKey() const;
private:
	Address address_;
	int executionCount_;
	int recordAttemptCount_;
	std::string basicBlockRecordKey_;
	static const int EXECUTION_COUNT_THRESHOLD;
	static const int RECORD_ATTEMPT_COUNT_THRESHOLD;
};

#endif