#include "InterpreterSimulatorEngine.h"

InterpreterSimulatorEngine::InterpreterSimulatorEngine(const std::vector<Byte>& rom, const IoBridge & ioBridge) : 
	SimulatorEngine(rom, ioBridge)
{}

void InterpreterSimulatorEngine::Run(Address startAddress)
{
	s_->pc = startAddress;
	bool running = true;
	while (running)
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
				// ignore
			}
		}
	}
}

