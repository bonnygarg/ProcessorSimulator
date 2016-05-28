#ifndef _IO_PERIPHERAL_H_
#define _IO_PERIPHERAL_H_

#include <cstdint>
#include <Global\Global.h>

class IoPeripheral
{
public:
	virtual Byte Read(Port port) = 0;
	virtual void Write(Port port, Byte data) = 0;
};

#endif
