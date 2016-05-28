#include "RomLoader.h"

void RomLoader::LoadFromFile(std::ifstream& fIn, std::vector<Byte>& rom, int romSize)
{
	if (fIn.is_open() == false)
		return;

	rom.clear();
	rom.resize(romSize, 0x00);
	int i = 0;
	char c;
	fIn.read(&c, 1);
	while (fIn.eof() == false)
	{
		rom[i] = ((Byte)c);
		++i;
		fIn.read(&c, 1);
	}
}