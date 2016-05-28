#ifndef _IO_BRIDGE_H_
#define _IO_BRIDGE_H_

#include <Global\Global.h>
#include "IoPeripheral.h"
#include <memory>
#include <map>

class IoBridge
{
public:
	void Map(Port port, std::shared_ptr<IoPeripheral> ioPeripheral);
	Byte Read(Port port) const;
	void Write(Port port, Byte byte) const;
private:
	std::map<Port, std::shared_ptr<IoPeripheral>> ioPeripheralsMap_;
	static const Byte DEFAULT_READ_VALUE;
};

#endif