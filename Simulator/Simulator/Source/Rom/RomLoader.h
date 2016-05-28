#ifndef _ROM_LOADER_H_
#define _ROM_LOADER_H_

#include <fstream>
#include <vector>
#include <Global\Global.h>

class RomLoader
{
public:
	static void LoadFromFile(std::ifstream& fIn, std::vector<Byte>& rom, int romSize);
};

#endif