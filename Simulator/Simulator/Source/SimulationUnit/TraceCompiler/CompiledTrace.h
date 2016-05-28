#ifndef _COMPILED_TRACE_H_
#define _COMPILED_TRACE_H_

#include <unordered_map>
#include <memory>

#include <Global\Global.h>
#include <SimulationUnit\SimulationUnit.h>
#include <State\State.h>
#include <Compiler\CompiledCode.h>
#include <Cfg\Cfg.h>
#include <Recorder\Recorder.h>
#include <Operation\Operation.h>

class TraceCompilerSimulatorEngine;

class CompiledTrace : public SimulationUnit
{
public:
	CompiledTrace(State* s, std::shared_ptr<Operation> operation, CompiledCode compiledCode, Address address, std::shared_ptr<Cfg> cfg, TraceCompilerSimulatorEngine& simulatorEngine, Recorder& recorder);
	void SetCompiledCode(const CompiledCode& compiledCode);
	void Run() override;
private:
	State* s_;
	std::shared_ptr<Operation> operation_;
	CompiledCode compiledCode_;
	Address address_;
	std::shared_ptr<Cfg> cfg_;
	TraceCompilerSimulatorEngine& simulatorEngine_;
	Recorder& recorder_;
	std::string sideExitBasicBlockRecordKey_;
	int traceAppendCount_;
};

#endif