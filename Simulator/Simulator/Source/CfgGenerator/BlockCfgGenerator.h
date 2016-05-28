#ifndef _BLOCK_CFG_GENERATOR_H_
#define _BLOCK_CFG_GENERATOR_H_

#include <sstream>
#include <memory>

#include <Global\Global.h>
#include <Cfg\Cfg.h>
#include <Cfg\BasicBlockRecord.h>
#include <Operation\OutgoingEdges\OutgoingEdgesVisitor.h>
#include <Decoder\Decoder.h>

class BlockCfgGenerator : public OutgoingEdgesVisitor
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
	std::string MakeBasicBlockRecordKeyFromAddress_(Address address);
	std::string MakeNonCompilableOperationRecordKeyFromAddress_(Address address);
	bool ShouldAbort_();

	bool isEndOfBasicBlockFound_;
	Address address_;
	int numberOfOperations_;
	std::shared_ptr<Operation> operation_;
	std::shared_ptr<BasicBlockRecord> basicBlockRecord_;
	std::shared_ptr<Cfg> cfg_;

	static const int MAX_NUMBER_OF_OPERATIONS_;
};

#endif