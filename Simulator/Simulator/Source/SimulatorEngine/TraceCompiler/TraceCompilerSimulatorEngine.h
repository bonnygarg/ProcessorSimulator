#ifndef _TRACE_COMPILER_SIMULATOR_UNIT_
#define _TRACE_COMPILER_SIMULATOR_UNIT_

#include <memory>
#include <unordered_map>

#include <SimulatorEngine\SimulatorEngine.h>
#include <SimulationUnit\SimulationUnit.h>
#include <SimulationUnit\TraceCompiler\InterpretedTraceAnchor.h>
#include <SimulationUnit\TraceCompiler\CompiledTrace.h>
#include <Cfg\Cfg.h>
#include <CfgGenerator\TraceCfgGenerator.h>
#include <Compiler\CompiledCode.h>
#include <Compiler\Compiler.h>
#include <Recorder\Recorder.h>

class TraceCompilerSimulatorEngine : public SimulatorEngine
{
public:
	TraceCompilerSimulatorEngine(const std::vector<Byte>& rom, const IoBridge& ioBridge);
	void CreateInterpretedTraceAnchor(Address address);
	void CreateCompiledTrace(Address address);
	void ExtendCompiledTrace(Address address, std::shared_ptr<Cfg> cfg, std::string sideExitBasicBlockRecordKey, int recordCount, CompiledTrace& compiledTrace);
	// Inherited via SimulatorEngine
	void Run(Address startAddress) override;
private:
	std::string MakeCfgKeyFromAddress_(Address address);

	std::unordered_map<Address, std::shared_ptr<SimulationUnit>> simulationUnitTable_;
	Compiler compiler_;
	TraceCfgGenerator cfgGenerator_;
	Recorder recorder_;
};

#endif