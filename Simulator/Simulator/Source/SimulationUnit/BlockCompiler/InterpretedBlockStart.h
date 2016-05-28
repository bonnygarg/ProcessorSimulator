#ifndef _INTERPRETED_BLOCK_START_H_
#define _INTERPRETED_BLOCK_START_H_

#include <memory>

#include <Global\Global.h>
#include <SimulationUnit\SimulationUnit.h>
#include <Operation\Operation.h>

class BlockCompilerSimulatorEngine;

class InterpretedBlockStart : public SimulationUnit
{
public:
	InterpretedBlockStart(std::shared_ptr<Operation> operation, Address startAddress, BlockCompilerSimulatorEngine& simulatorEngine);
	void Run() override;

private:
	bool IsHot_();
	bool IsRecordable_();

	std::shared_ptr<Operation> operation_;
	Address startAddress_;
	BlockCompilerSimulatorEngine& simulatorEngine_;
	int executionCount_;
	int recordAttemptCount_;
	static const int EXECUTION_COUNT_THRESHOLD_;
	static const int RECORD_ATTEMPT_COUNT_THRESHOLD_;
};

#endif