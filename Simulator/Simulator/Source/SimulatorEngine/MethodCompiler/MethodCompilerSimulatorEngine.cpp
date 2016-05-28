#include "MethodCompilerSimulatorEngine.h"
#include "MethodCompilerFirstPass.h"

MethodCompilerSimulatorEngine::MethodCompilerSimulatorEngine(const std::vector<Byte>& rom, const IoBridge & ioBridge) :
	SimulatorEngine(rom, ioBridge),
	compiler_(s_),
	cfgGenerator_()
{
	MethodCompilerFirstPass firstPass;
	firstPass.Perform(s_, 0x0000, decoder_, &simulationUnitTable_, *this);
}

void MethodCompilerSimulatorEngine::CreateInterpretedMethodStart(Address address)
{
	auto operation = decoder_.Decode(address);
	if (operation)
	{
		std::shared_ptr<Operation> operationShared(std::move(operation));
		std::shared_ptr<SimulationUnit> ibs = std::make_shared<InterpretedMethodStart>(operationShared, address, *this);
		simulationUnitTable_.insert(std::make_pair(address, ibs));
	}
}

void MethodCompilerSimulatorEngine::CreateCompiledMethod(Address address)
{
	std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>(MakeCfgKeyFromAddress_(address));
	bool isCfgGenerated = cfgGenerator_.CreateCfg(decoder_, address, cfg);
	if (isCfgGenerated == true)
	{
		CompiledCode compiledCode;
		bool isCompilationSuccessful = compiler_.Compile(cfg, compiledCode);
		if (isCompilationSuccessful) 
		{
			std::shared_ptr<CompiledMethod> compiledMethod = std::make_shared<CompiledMethod>(s_, compiledCode);
			simulationUnitTable_.erase(address);
			simulationUnitTable_.insert(std::make_pair(address, compiledMethod));
		}
	}
}

void MethodCompilerSimulatorEngine::Run(Address startAddress)
{
	s_->pc = startAddress;
	bool running = true;
	while (running)
	{
		auto simulationUnit = simulationUnitTable_.find(s_->pc);
		if (simulationUnit != simulationUnitTable_.end())
		{
			simulationUnit->second->Run();
		}
		else
		{
			auto operation = decoder_.Decode(s_->pc);
			if (operation)
			{
				operation->Run();
			}
			else
			{
				s_->isInterrupted = true;
				s_->interruptType = InterruptType::UnknownOpcode;
			}
		}
		if (s_->isInterrupted)
		{
			if (s_->interruptType == InterruptType::Halted)
			{
				s_->isInterrupted = false;
				running = false;
			}
			else if (s_->interruptType == InterruptType::UnknownOpcode)
			{
				// handle error
			}
			else if (s_->interruptType == InterruptType::CodeModified)
			{
				// handle
			}
		}
	}
}

std::string MethodCompilerSimulatorEngine::MakeCfgKeyFromAddress_(Address address)
{
	std::ostringstream outstr;
	outstr << "fn" << address;
	return outstr.str();
}
