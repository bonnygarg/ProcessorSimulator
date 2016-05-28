#include "InterpretedTraceAnchor.h"

#include <SimulatorEngine\TraceCompiler\TraceCompilerSimulatorEngine.h>

const int InterpretedTraceAnchor::EXECUTION_COUNT_THRESHOLD_ = 10;
const int InterpretedTraceAnchor::RECORD_ATTEMPT_COUNT_THRESHOLD_ = 2;

InterpretedTraceAnchor::InterpretedTraceAnchor(std::shared_ptr<Operation> operation, Address anchorAddress, TraceCompilerSimulatorEngine & simulatorEngine, Recorder & recorder) :
	operation_(operation),
	anchorAddress_(anchorAddress),
	simulatorEngine_(simulatorEngine),
	recorder_(recorder),
	executionCount_(0),
	recordAttemptCount_(0)
{}

void InterpretedTraceAnchor::Run()
{
	operation_->Run();
	++executionCount_;
	if (recorder_.IsRecording() == false)
	{
		if (IsHot_() && IsRecordable_())
		{
			++recordAttemptCount_;
			recorder_.StartRecording(anchorAddress_);
			recorder_.AddToRecording(RecordedOperation(anchorAddress_, operation_));
		}
	}
	else
	{
		if (anchorAddress_ == recorder_.GetRecordingStartAddress())
		{
			recorder_.StopRecording();
			simulatorEngine_.CreateCompiledTrace(anchorAddress_);
		}
		else
		{
			recorder_.AddToRecording(RecordedOperation(anchorAddress_, operation_));
		}
	}
}

bool InterpretedTraceAnchor::IsHot_()
{
	return (executionCount_ > InterpretedTraceAnchor::EXECUTION_COUNT_THRESHOLD_);
}

bool InterpretedTraceAnchor::IsRecordable_()
{
	return (recordAttemptCount_ < InterpretedTraceAnchor::RECORD_ATTEMPT_COUNT_THRESHOLD_);
}