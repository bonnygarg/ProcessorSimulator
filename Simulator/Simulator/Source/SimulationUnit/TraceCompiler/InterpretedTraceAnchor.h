#ifndef _INTERPRETED_TRACE_ANCHOR_H_
#define _INTERPRETED_TRACE_ANCHOR_H_

#include <memory>

#include <Global\Global.h>
#include <SimulationUnit\SimulationUnit.h>
#include <Operation\Operation.h>
#include <Recorder\RecordedOperation.h>
#include <Recorder\Recorder.h>

class TraceCompilerSimulatorEngine;

class InterpretedTraceAnchor : public SimulationUnit
{
public:
	InterpretedTraceAnchor(std::shared_ptr<Operation> operation, Address anchorAddress, TraceCompilerSimulatorEngine& simulatorEngine, Recorder& recorder);
	// Inherited via SimulationUnit
	virtual void Run() override;
private:
	bool IsHot_();
	bool IsRecordable_();

	std::shared_ptr<Operation> operation_;
	Address anchorAddress_;
	TraceCompilerSimulatorEngine& simulatorEngine_;
	int executionCount_;
	int recordAttemptCount_;
	Recorder& recorder_;
	static const int EXECUTION_COUNT_THRESHOLD_;
	static const int RECORD_ATTEMPT_COUNT_THRESHOLD_;
};

#endif