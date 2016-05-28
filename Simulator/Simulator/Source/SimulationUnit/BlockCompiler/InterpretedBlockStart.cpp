#include "InterpretedBlockStart.h"
#include <SimulatorEngine\BlockCompiler\BlockCompilerSimulatorEngine.h>

const int InterpretedBlockStart::EXECUTION_COUNT_THRESHOLD_ = 10;
const int InterpretedBlockStart::RECORD_ATTEMPT_COUNT_THRESHOLD_= 2;

InterpretedBlockStart::InterpretedBlockStart(std::shared_ptr<Operation> operation, Address startAddress, BlockCompilerSimulatorEngine & simulatorEngine) :
	operation_(operation),
	startAddress_(startAddress),
	simulatorEngine_(simulatorEngine),
	executionCount_(0),
	recordAttemptCount_(0)
{}

void InterpretedBlockStart::Run()
{
	operation_->Run();
	++executionCount_;
	if (IsHot_() && IsRecordable_())
	{
		++recordAttemptCount_;
		simulatorEngine_.CreateCompiledBlock(startAddress_);
	}
}

bool InterpretedBlockStart::IsHot_()
{
	return (executionCount_ > InterpretedBlockStart::EXECUTION_COUNT_THRESHOLD_);
}

bool InterpretedBlockStart::IsRecordable_()
{
	return (recordAttemptCount_ < InterpretedBlockStart::RECORD_ATTEMPT_COUNT_THRESHOLD_);
}
