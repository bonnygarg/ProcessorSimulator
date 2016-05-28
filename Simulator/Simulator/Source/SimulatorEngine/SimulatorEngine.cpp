#include "SimulatorEngine.h"

SimulatorEngine::SimulatorEngine(const std::vector<Byte>& rom, const IoBridge & ioBridge) :
	state_(),
	s_(&state_),
	ioBridge_(ioBridge),
	decoder_(s_, ioBridge_),
	rom_size_(rom.size())
{
	s_->interpretedCount = new int[rom_size_]();
	s_->nativelyExecutedCount = new int[rom_size_]();
	SetMemory(rom);
}

void SimulatorEngine::SetMemory(const std::vector<Byte>& rom)
{
	if (s_->m != nullptr)
		delete[] s_->m;
	s_->m = new Memory[rom_size_];
	for (int i = 0; i < rom_size_; ++i)
		s_->m[i].byte = rom[i];
}

std::vector<int> SimulatorEngine::GetInterpertedCount() const
{
	std::vector<int> interpretedCount;
	interpretedCount.resize(rom_size_, 0);
	for (int i = 0; i < rom_size_; ++i)
		interpretedCount[i] = s_->interpretedCount[i];
	return interpretedCount;
}

std::vector<int> SimulatorEngine::GetNativelyExecutedCount() const
{
	std::vector<int> nativelyExecutedCount;
	nativelyExecutedCount.resize(rom_size_, 0);
	for (int i = 0; i < rom_size_; ++i)
		nativelyExecutedCount[i] = s_->nativelyExecutedCount[i];
	return nativelyExecutedCount;
}
