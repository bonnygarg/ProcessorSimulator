#include "TraceCompilerSimulatorEngine.h"
#include "TraceCompilerFirstPass.h"

TraceCompilerSimulatorEngine::TraceCompilerSimulatorEngine(const std::vector<Byte>& rom, const IoBridge & ioBridge) :
	SimulatorEngine(rom, ioBridge),
	compiler_(s_),
	cfgGenerator_(),
	recorder_()
{
	TraceCompilerFirstPass firstPass;
	firstPass.Perform(s_, 0x0000, decoder_, &simulationUnitTable_, *this);
}

void TraceCompilerSimulatorEngine::CreateInterpretedTraceAnchor(Address address)
{
	auto operation = decoder_.Decode(address);
	if (operation)
	{
		std::shared_ptr<Operation> operationShared(std::move(operation));
		std::shared_ptr<SimulationUnit> ibs = std::make_shared<InterpretedTraceAnchor>(operationShared, address, *this, recorder_);
		simulationUnitTable_.insert(std::make_pair(address, ibs));
	}
}

void TraceCompilerSimulatorEngine::CreateCompiledTrace(Address address)
{
	auto operation = decoder_.Decode(address);
	if (operation)
	{
		std::shared_ptr<Operation> operationShared(std::move(operation));

		std::shared_ptr<Cfg> cfg = std::make_shared<Cfg>(MakeCfgKeyFromAddress_(address));
		bool isCfgGenerated = cfgGenerator_.CreateCfg(recorder_.GetRecordedOperations(), cfg);
		if (isCfgGenerated == true)
		{
			CompiledCode compiledCode;
			bool isCompilationSuccessful = compiler_.Compile(cfg, compiledCode);
			if (isCompilationSuccessful)
			{
				std::shared_ptr<CompiledTrace> compiledTrace = std::make_shared<CompiledTrace>(s_, operationShared, compiledCode, address, cfg, *this, recorder_);
				simulationUnitTable_.erase(address);
				simulationUnitTable_.insert(std::make_pair(address, compiledTrace));
			}
		}
	}
}

void TraceCompilerSimulatorEngine::ExtendCompiledTrace(Address address, std::shared_ptr<Cfg> cfg, std::string sideExitBasicBlockRecordKey, int recordCount, CompiledTrace& compiledTrace)
{
	bool isCfgGenerated = cfgGenerator_.ExtendCfg(recorder_.GetRecordedOperations(), cfg, sideExitBasicBlockRecordKey, address, recordCount);
	if (isCfgGenerated == true)
	{
		CompiledCode compiledCode;
		bool isCompilationSuccessful = compiler_.Compile(cfg, compiledCode);
		if (isCompilationSuccessful)
		{
			compiledTrace.SetCompiledCode(compiledCode);
		}
	}
}


void TraceCompilerSimulatorEngine::Run(Address startAddress)
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
				if (recorder_.IsRecording() == true)
				{
					std::shared_ptr<Operation> operationShared(std::move(operation));
					recorder_.AddToRecording(RecordedOperation(s_->pc, operationShared));
					operationShared->Run();
				}
				else
				{
					operation->Run();
				}
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

std::string TraceCompilerSimulatorEngine::MakeCfgKeyFromAddress_(Address address)
{
	std::ostringstream outstr;
	outstr << "fn" << address;
	return outstr.str();
}
