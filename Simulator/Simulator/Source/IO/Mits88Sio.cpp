#include "Mits88Sio.h"
#include <conio.h>

const int Mits88Sio::OPB_MAX_SIZE = 100;
const int Mits88Sio::IPB_MAX_SIZE = 20;
const Byte Mits88Sio::DEFAULT_READ_VALUE = 0x00;

Mits88Sio::Mits88Sio(std::ostream& os) : statusRegister_(0x01), os_(os)
{
	std::thread readFromOpbThread(&Mits88Sio::ReadFromOpb_, this);
	readFromOpbThread.detach();

	std::thread writeIntoIpbThread(&Mits88Sio::WriteIntoIpb_, this);
	writeIntoIpbThread.detach();
}

Byte Mits88Sio::Read(Port port)
{
	if (port & 0x01) // input
	{
		return ReadFromIpb_();
	}
	else if (!(port & 0x01)) // status register
	{
		return ReadStatusRegister_();
	}
	else if (port == 0xff) // front panel switch sense port
	{
		return 0x00;
	}
	else
	{
		return Byte();
	}
}

void Mits88Sio::Write(Port port, Byte data)
{
	if (port & 0x01) // output
	{
		WriteIntoOpb_(data);
	}
	else if (!(port & 0x01)) // control register
	{
		// ignore
	}
}

bool Mits88Sio::IsOpbFull_()
{
	return (opb_.size() >= Mits88Sio::OPB_MAX_SIZE);
}

bool Mits88Sio::IsOpbEmpty_()
{
	return (opb_.empty());
}

void Mits88Sio::WriteIntoOpb_(Byte data)
{
	std::unique_lock<std::mutex> opbLock(opbMutex_);
	while (IsOpbFull_())
		opbNotFullCv_.wait(opbLock);
	opb_.push(data);
	opbLock.unlock();
	opbNotEmptyCv_.notify_one();
}

void Mits88Sio::ReadFromOpb_()
{
	while (1)
	{
		std::unique_lock<std::mutex> opbLock(opbMutex_);
		while (IsOpbEmpty_())
			opbNotEmptyCv_.wait(opbLock);
		Byte data = opb_.front();
		opb_.pop();
		opbLock.unlock();
		opbNotFullCv_.notify_one();
		os_ << data;
	}
}

bool Mits88Sio::IsIpbFull_()
{
	return (ipb_.size() >= Mits88Sio::IPB_MAX_SIZE);
}

bool Mits88Sio::IsIpbEmpty_()
{
	return (ipb_.empty());
}

void Mits88Sio::WriteIntoIpb_()
{
	char c = _getch();
	while (1)
	{
		std::unique_lock<std::mutex> ipbLock(ipbMutex_);
		while (IsIpbFull_())
			ipbNotFullCv_.wait(ipbLock);
		Byte data = (Byte)c;
		ipb_.push(data);
		statusRegister_ &= (~0x01); // reset bit 0
		ipbLock.unlock();
		ipbNotEmptyCv_.notify_one();
		c = _getch();
	}
}

Byte Mits88Sio::ReadFromIpb_()
{
	std::unique_lock<std::mutex> ipbLock(ipbMutex_);
	if (IsIpbEmpty_())
	{
		statusRegister_ |= 0x01; // set bit 0
		return Mits88Sio::DEFAULT_READ_VALUE;
	}
	else
	{
		Byte data = ipb_.front();
		ipb_.pop();
		if (IsIpbEmpty_())
			statusRegister_ |= 0x01; // set bit 0
		ipbLock.unlock();
		ipbNotFullCv_.notify_one();
		return data;
	}
}


Byte Mits88Sio::ReadStatusRegister_()
{
	std::unique_lock<std::mutex> ipbLock(ipbMutex_);
	Byte data = statusRegister_;
	ipbLock.unlock();
	return data;
}
