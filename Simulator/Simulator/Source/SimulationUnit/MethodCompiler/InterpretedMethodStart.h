#ifndef _INTERPRETED_METHOD_START_H_
#define _INTERPRETED_METHOD_START_H_

#include <memory>

#include <Global\Global.h>
#include <SimulationUnit\SimulationUnit.h>
#include <Operation\Operation.h>

class MethodCompilerSimulatorEngine;

class InterpretedMethodStart : public SimulationUnit
{
public:
	InterpretedMethodStart(std::shared_ptr<Operation> operation, Address startAddress, MethodCompilerSimulatorEngine& simulatorEngine);
	void Run() override;

private:
	bool IsHot_();
	bool IsRecordable_();

	std::shared_ptr<Operation> operation_;
	Address startAddress_;
	MethodCompilerSimulatorEngine& simulatorEngine_;
	int executionCount_;
	int recordAttemptCount_;
	static const int EXECUTION_COUNT_THRESHOLD_;
	static const int RECORD_ATTEMPT_COUNT_THRESHOLD_;
};

#endif