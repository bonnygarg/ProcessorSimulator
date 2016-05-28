#ifndef _METHOD_CFG_GENERATOR_H_
#define _METHOD_CFG_GENERATOR_H_

#include <sstream>
#include <memory>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

#include <Global\Global.h>
#include <Cfg\Cfg.h>
#include <Cfg\BasicBlockRecord.h>
#include <Cfg\MethodRecord.h>
#include <Operation\OutgoingEdges\OutgoingEdgesVisitor.h>
#include <Decoder\Decoder.h>

class MethodCfgGenerator : public OutgoingEdgesVisitor
{
public:
	bool CreateCfg(Decoder& decoder, Address startAddress, std::shared_ptr<Cfg> cfg);
	// Inherited via OutgoingEdgesVisitor
	virtual void Visit(UnconditionalJumpOutgoingEdges& og) override;
	virtual void Visit(ConditionalJumpOutgoingEdges& og) override;
	virtual void Visit(UnconditionalCallOutgoingEdges& og) override;
	virtual void Visit(ConditionalCallOutgoingEdges& og) override;
	virtual void Visit(UnconditionalReturnOutgoingEdges& og) override;
	virtual void Visit(ConditionalReturnOutgoingEdges& og) override;
	virtual void Visit(NextOutgoingEdges& og) override;
	virtual void Visit(NonCompilableOutgoingEdges& og) override;
	virtual void Visit(NoneOutgoingEdges& og) override;
private:
	std::string MakeBasicBlockRecordKey_(Address methodStartAddress, Address blockStartAddress);
	std::string MakeNonCompilableOperationRecordKey_(Address methodStartAddress, Address blockStartAddress, Address operationAddress);
	bool ShouldAbort_();
	void AddToDiscoveredBasicBlockRecordQueue_(Address address);
	void AddToDiscoveredMethodRecordQueue_(Address startAddress, std::string returnToBasicBlockRecord);

	std::queue<Address> toProcessBasicBlockRecords_;
	std::unordered_set<Address> discoveredBasicBlockRecords_;
	
	std::queue<Address> toProcessMethodRecords_;
	std::unordered_map<Address, MethodRecord> discoveredMethodRecords_;

	std::shared_ptr<Cfg> cfg_;
	std::unordered_map<Address, MethodRecord>::iterator currentMethodRecordIterator_;
	std::shared_ptr<BasicBlockRecord> currentBasicBlockRecord_;
	bool isEndOfBasicBlockFound_;
	Address address_;
	int numberOfOperations_;
	std::shared_ptr<Operation> operation_;

	static const int MAX_NUMBER_OF_OPERATIONS_;
};

#endif