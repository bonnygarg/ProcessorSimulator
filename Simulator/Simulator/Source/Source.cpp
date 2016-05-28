#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <Global\Global.h>
#include <Rom\RomLoader.h>
#include <IO\IoBridge.h>
#include <IO\Mits88Sio.h>
#include <SimulatorEngine\Interpreter\InterpreterSimulatorEngine.h>
#include <SimulatorEngine\BlockCompiler\BlockCompilerSimulatorEngine.h>
#include <SimulatorEngine\MethodCompiler\MethodCompilerSimulatorEngine.h>
#include <SimulatorEngine\TraceCompiler\TraceCompilerSimulatorEngine.h>
#include <Time\Timer.h>

int main()
{
	std::string romFileName;
	std::cout << "Rom? ";
	std::cin >> romFileName;
	
	int count;
	std::cout << "Number of iterations? ";
	std::cin >> count;
	
	char engineType;
	std::cout << "Simulator Engine (i/b/m/t)? ";
	std::cin >> engineType;

	std::ifstream fIn(romFileName, std::ios::in | std::ios::binary);
	std::vector<Byte> rom;
	RomLoader::LoadFromFile(fIn, rom, 65536);
	fIn.close();

	auto mits88Sio = std::make_shared<Mits88Sio>(std::cout);
	IoBridge ioBridge;
	ioBridge.Map(0x00, mits88Sio);
	ioBridge.Map(0x01, mits88Sio);
	
	std::unique_ptr<SimulatorEngine> se;
	if (engineType == 'b')
		se = std::make_unique<BlockCompilerSimulatorEngine>(rom, ioBridge);
	else if (engineType == 'm')
		se = std::make_unique<MethodCompilerSimulatorEngine>(rom, ioBridge);
	else if (engineType == 't')
		se = std::make_unique<TraceCompilerSimulatorEngine>(rom, ioBridge);
	else
		se = std::make_unique<InterpreterSimulatorEngine>(rom, ioBridge);
	
	Timer timer;	

	std::ofstream fOutTime("time.benchmark", std::ios::out);

	for (int i = 0; i < count; ++i)
	{
		se->SetMemory(rom);
		timer.Start();
		se->Run(0x00);
		timer.Stop();
		std::cout << i << "\t" << timer.GetTimeElapsedInMilli() << std::endl;
		fOutTime << i << "\t" << timer.GetTimeElapsedInMilli() << std::endl;
	}

	fOutTime.close();

	std::ofstream fOutInterpretedCount("int_count.benchmark", std::ios::out);
	auto interpretedCount = se->GetInterpertedCount();
	fOutInterpretedCount.fill('0');
	for (int i = 0; i < interpretedCount.size(); ++i)
	{
		fOutInterpretedCount << std::hex << std::setw(4) << i << "\t";
		fOutInterpretedCount << std::dec << interpretedCount[i] << std::endl;
	}
	fOutInterpretedCount.close();

	std::ofstream fOutNativelyExecutedCount("ne_count.benchmark", std::ios::out);
	auto nativelyExecutedCount = se->GetNativelyExecutedCount();
	fOutNativelyExecutedCount.fill('0');
	for (int i = 0; i < nativelyExecutedCount.size(); ++i)
	{
		fOutNativelyExecutedCount << std::hex << std::setw(4) << i << "\t";
		fOutNativelyExecutedCount << std::dec << nativelyExecutedCount[i] << std::endl;
	}
	fOutNativelyExecutedCount.close();

	std::cout << std::endl << "Press [ENTER] to continue..." << std::endl;
	std::fflush(stdin);
	std::getchar();
	return 0;
}