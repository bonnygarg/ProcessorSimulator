#ifndef _BLOCK_COMPILER_SIMULATOR_UNIT_
#define _BLOCK_COMPILER_SIMULATOR_UNIT_

#include <memory>
#include <unordered_map>

#include <SimulatorEngine\SimulatorEngine.h>
#include <SimulationUnit\SimulationUnit.h>
#include <SimulationUnit\BlockCompiler\InterpretedBlockStart.h>
#include <SimulationUnit\BlockCompiler\CompiledBlock.h>
#include <Cfg\Cfg.h>
#include <CfgGenerator\BlockCfgGenerator.h>
#include <Compiler\CompiledCode.h>
#include <Compiler\Compiler.h>

class BlockCompilerSimulatorEngine : public SimulatorEngine
{
public:
	BlockCompilerSimulatorEngine(const std::vector<Byte>& rom, const IoBridge& ioBridge);
	void CreateInterpretedBlockStart(Address address);
	void CreateCompiledBlock(Address address);

	// Inherited via SimulatorEngine
	void Run(Address startAddress) override;
private:
	std::string MakeCfgKeyFromAddress_(Address address);

	std::unordered_map<Address, std::shared_ptr<SimulationUnit>> simulationUnitTable_;
	Compiler compiler_;
	BlockCfgGenerator cfgGenerator_;
};

#endif