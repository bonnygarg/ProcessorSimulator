#ifndef _CFG_H_
#define _CFG_H_

#include <unordered_map>
#include <vector>
#include <memory>
#include <string>



#include "BasicBlockRecord.h"
#include "NonCompilableOperationRecord.h"
#include <Global\Global.h>
#include <Operation\Operation.h>

class Cfg
{
public:
	Cfg(const std::string& key);
	
	std::string GetKey() const;
	
	const std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>>& GetBasicBlockRecords() const;
	std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>>& GetBasicBlockRecords();
	void SetBasicBlockRecords(const std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>>& basicBlockRecords);

	const std::vector<std::string>& GetEntryBasicBlockRecords() const;
	std::vector<std::string>& GetEntryBasicBlockRecords();
	void SetEntryBasicBlockRecords(const std::vector<std::string>& entryBasicBlockRecords);

	const std::unordered_map<std::string, NonCompilableOperationRecord>& GetNonCompilableOperationRecords() const;
	std::unordered_map<std::string, NonCompilableOperationRecord>& GetNonCompilableOperationRecords();
	void SetNonCompilableOperationRecords(const std::unordered_map<std::string, NonCompilableOperationRecord>& nonCompilableOperationRecords);

	void Clear();
private:
	std::string key_;
	std::unordered_map<std::string, std::shared_ptr<BasicBlockRecord>> basicBlockRecords_;
	std::vector<std::string> entryBasicBlockRecords_;
	std::unordered_map<std::string, NonCompilableOperationRecord> nonCompilableOperationRecords_;
};

#endif