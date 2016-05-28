#include "CompiledTrace.h"

#include <SimulatorEngine\TraceCompiler\TraceCompilerSimulatorEngine.h>

CompiledTrace::CompiledTrace(State* s, std::shared_ptr<Operation> operation, CompiledCode compiledCode, Address address, std::shared_ptr<Cfg> cfg, TraceCompilerSimulatorEngine& simulatorEngine, Recorder& recorder) :
	s_(s),
	operation_(operation),
	compiledCode_(compiledCode),
	address_(address),
	cfg_(cfg),
	simulatorEngine_(simulatorEngine),
	recorder_(recorder),
	sideExitBasicBlockRecordKey_(),
	traceAppendCount_(0)
{}

void CompiledTrace::SetCompiledCode(const CompiledCode & compiledCode)
{
	compiledCode_ = compiledCode;
}

void CompiledTrace::Run()
{
	if (recorder_.IsRecording() == false)
	{
		s_->resumeFromRecordIndex = 0;
		while (s_->resumeFromRecordIndex != -1)
		{
			auto compilationUnit = compiledCode_.GetCompilationUnitTable()[s_->resumeFromRecordIndex];
			compilationUnit->Run();
		}
		// trace exits only through a side exit
		auto sideExit = &compiledCode_.GetSideExitTable()[s_->sideExitIndex];
		sideExit->IncrementExecutionCount();
		if (sideExit->IsHot() && sideExit->IsRecordable())
		{
			sideExit->IncrementRecordAttemptCount();
			sideExitBasicBlockRecordKey_ = sideExit->GetBasicBlockRecordKey();
			recorder_.StartRecording(address_);
		}
	}
	else
	{
		operation_->Run();
		if (address_ == recorder_.GetRecordingStartAddress())
		{
			// successfully finished recording a side exit
			++traceAppendCount_;
			recorder_.StopRecording();
			simulatorEngine_.ExtendCompiledTrace(address_, cfg_, sideExitBasicBlockRecordKey_, traceAppendCount_, *this);
		}
		else
		{
			// we stumbled upon this compiled trace
			// while recording some other trace
			// there is a change of being stuck in a loop
			// but recorder automatically handles that for us :)
			recorder_.AddToRecording(RecordedOperation(address_, operation_));
		}
	}

}
