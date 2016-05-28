#ifndef _INTERPRETER_SIMULATOR_UNIT_
#define _INTERPRETER_SIMULATOR_UNIT_

#include <SimulatorEngine\SimulatorEngine.h>

class InterpreterSimulatorEngine : public SimulatorEngine
{
public:
	InterpreterSimulatorEngine(const std::vector<Byte>& rom, const IoBridge& ioBridge);

	// Inherited via SimulatorEngine
	void Run(Address startAddress) override;

};

#endif