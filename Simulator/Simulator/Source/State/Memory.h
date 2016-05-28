#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <Global\Global.h>

class Memory
{
public:
	Byte byte;
	bool isCode;
	bool isStart;
	bool isEnd;
	bool isMethodStart;
	bool isAnchor;
	
	Memory() : 
		byte(),
		isCode(false),
		isStart(false),
		isEnd(false),
		isMethodStart(false),
		isAnchor(false)
	{}
	
};

#endif