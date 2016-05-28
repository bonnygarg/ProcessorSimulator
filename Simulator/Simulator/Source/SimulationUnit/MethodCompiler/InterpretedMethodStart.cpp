#include "InterpretedMethodStart.h"
#include <SimulatorEngine\MethodCompiler\MethodCompilerSimulatorEngine.h>

const int InterpretedMethodStart::EXECUTION_COUNT_THRESHOLD_ = 10;
const int InterpretedMethodStart::RECORD_ATTEMPT_COUNT_THRESHOLD_ = 2;


InterpretedMethodStart::InterpretedMethodStart(std::shared_ptr<Operation> operation, Address startAddress, MethodCompilerSimulatorEngine & simulatorEngine) :
	operation_(operation),
	startAddress_(startAddress),
	simulatorEngine_(simulatorEngine),
	executionCount_(0),
	recordAttemptCount_(0)
{}

void InterpretedMethodStart::Run()
{
	operation_->Run();
	++executionCount_;
	if (IsHot_() && IsRecordable_())
	{
		++recordAttemptCount_;
		simulatorEngine_.CreateCompiledMethod(startAddress_);
	}
}

bool InterpretedMethodStart::IsHot_()
{
	return (executionCount_ > InterpretedMethodStart::EXECUTION_COUNT_THRESHOLD_);
}

bool InterpretedMethodStart::IsRecordable_()
{
	return (recordAttemptCount_ < InterpretedMethodStart::RECORD_ATTEMPT_COUNT_THRESHOLD_);
}
