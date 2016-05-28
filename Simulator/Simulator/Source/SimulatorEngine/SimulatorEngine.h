#ifndef _SIMULATOR_ENGINE_
#define _SIMULATOR_ENGINE_

#include <vector>
#include <Global\Global.h>
#include <IO\IoBridge.h>
#include <Decoder\Decoder.h>

class SimulatorEngine
{
public:
	SimulatorEngine(const std::vector<Byte>& rom, const IoBridge& ioBridge);
	virtual void Run(Address startAddress) = 0;
	virtual void SetMemory(const std::vector<Byte>& rom);
	virtual std::vector<int> GetInterpertedCount() const;
	virtual std::vector<int> GetNativelyExecutedCount() const;
protected:
	State state_;
	State* s_;
	IoBridge ioBridge_;
	Decoder decoder_;
	size_t rom_size_;
};


#endif