#ifndef _MITS_88_SIO_H_
#define _MITS_88_SIO_H_

#include "IoPeripheral.h"

#include <condition_variable>
#include <mutex>
#include <thread>

#include <queue>

#include <iostream>

class Mits88Sio : public IoPeripheral
{
public:
	Mits88Sio(std::ostream& os);
	Byte Read(Port port) override;
	void Write(Port port, Byte data) override;
private:
	// output buffer functions
	bool IsOpbFull_();
	bool IsOpbEmpty_();
	void ReadFromOpb_();
	void WriteIntoOpb_(Byte data);

	// input buffer functions
	bool IsIpbFull_();
	bool IsIpbEmpty_();
	Byte ReadFromIpb_();
	void WriteIntoIpb_();

	// status register functions
	Byte ReadStatusRegister_();

	//status register
	Byte statusRegister_;

	// output buffer
	static const int OPB_MAX_SIZE;
	std::queue<Byte> opb_;
	std::mutex opbMutex_;
	std::condition_variable opbNotFullCv_;
	std::condition_variable opbNotEmptyCv_;
	std::ostream& os_;

	// input buffer
	static const int IPB_MAX_SIZE;
	std::queue<Byte> ipb_;
	std::mutex ipbMutex_;
	std::condition_variable ipbNotFullCv_;
	std::condition_variable ipbNotEmptyCv_;

	static const Byte DEFAULT_READ_VALUE;
};

#endif
