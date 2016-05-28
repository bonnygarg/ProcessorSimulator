#include "IoBridge.h"

const Byte IoBridge::DEFAULT_READ_VALUE = 0x00;

void IoBridge::Map(Port port, std::shared_ptr<IoPeripheral> ioPeripheral)
{
	ioPeripheralsMap_[port] = ioPeripheral;
}

Byte IoBridge::Read(Port port) const
{
	auto ioPeripheralIt = ioPeripheralsMap_.find(port);
	if (ioPeripheralIt != ioPeripheralsMap_.end())
		return ioPeripheralIt->second->Read(port);
	else
		return IoBridge::DEFAULT_READ_VALUE;
}

void IoBridge::Write(Port port, Byte byte) const
{
	auto ioPeripheralIt = ioPeripheralsMap_.find(port);
	if (ioPeripheralIt != ioPeripheralsMap_.end())
		ioPeripheralIt->second->Write(port, byte);
}
