#ifndef _METHOD_COMPILER_SIMULATOR_UNIT_
#define _METHOD_COMPILER_SIMULATOR_UNIT_

#include <memory>
#include <unordered_map>

#include <SimulatorEngine\SimulatorEngine.h>
#include <SimulationUnit\SimulationUnit.h>
#include <SimulationUnit\MethodCompiler\InterpretedMethodStart.h>
#include <SimulationUnit\MethodCompiler\CompiledMethod.h>
#include <Cfg\Cfg.h>
#include <CfgGenerator\MethodCfgGenerator.h>
#include <Compiler\CompiledCode.h>
#include <Compiler\Compiler.h>

class MethodCompilerSimulatorEngine : public SimulatorEngine
{
public:
	MethodCompilerSimulatorEngine(const std::vector<Byte>& rom, const IoBridge& ioBridge);
	void CreateInterpretedMethodStart(Address address);
	void CreateCompiledMethod(Address address);

	// Inherited via SimulatorEngine
	void Run(Address startAddress) override;
private:
	std::string MakeCfgKeyFromAddress_(Address address);

	std::unordered_map<Address, std::shared_ptr<SimulationUnit>> simulationUnitTable_;
	Compiler compiler_;
	MethodCfgGenerator cfgGenerator_;
};

#endif