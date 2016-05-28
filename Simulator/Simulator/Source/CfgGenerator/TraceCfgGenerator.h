#ifndef _TRACE_CFG_GENERATOR_H_
#define _TRACE_CFG_GENERATOR_H_

#include <sstream>
#include <memory>
#include <vector>

#include <Global\Global.h>
#include <Cfg\Cfg.h>
#include <Cfg\BasicBlockRecord.h>
#include <Operation\OutgoingEdges\OutgoingEdgesVisitor.h>
#include <Recorder\RecordedOperation.h>

class TraceCfgGenerator : public OutgoingEdgesVisitor
{
public:
	bool CreateCfg(const std::vector<RecordedOperation>& recordedOperations, std::shared_ptr<Cfg> cfg);
	bool ExtendCfg(const std::vector<RecordedOperation>& recordedOperations, std::shared_ptr<Cfg> cfg, std::string sideExitBasicBlockRecordKey, Address anchorAddress, int recordCount);
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
	std::string MakeBasicBlockRecordKey_(int recordCount, const std::list<Address>& callStack, Address parentBasicBlockRecordStartAddress, Address basicBlockRecordStartAddress);
	std::string MakeNonCompilableOperationRecordKey_(std::string basicBlockRecordKey, Address operationAddress);
	bool IsRecursiveCall_(const std::list<Address> callStack, Address newReturnAddress);

	bool isEndOfBasicBlockFound_;
	Address anchorAddress_;
	std::shared_ptr<Operation> operation_;
	std::shared_ptr<BasicBlockRecord> currentBasicBlockRecord_;
	const std::vector<RecordedOperation>* recordedOperations_;
	size_t recordedOperationsIndex_;
	int recordCount_;
	bool shouldAbort_;
	std::shared_ptr<Cfg> cfg_;

	static const std::string ANCHOR_BASIC_BLOCK_RECORD_KEY;
};

#endif