#ifndef _STATE_H_
#define _STATE_H_

#include <Global\Global.h>
#include "Memory.h"
#include "InterruptType.h"

class State
{
public:
	State() :
		a(0), b(0), c(0), d(0), e(0), h(0), l(0), pc(0), parentBlockPc(0), sp(0),
		cf(false), sf(false), zf(false), pf(false), af(false),
		ie(true),
		m(nullptr),
		isInterrupted(false), interruptType(InterruptType::None),
		resumeFromRecordIndex(-1), sideExitIndex(-1),
		interpretedCount(nullptr), nativelyExecutedCount(nullptr)
	{}

	void SetSf()
	{
		sf = ((a & 0x80) == 0x80);
	}

	void SetSf(Byte operand)
	{
		sf = ((operand & 0x80) == 0x80);
	}

	void SetZf()
	{
		zf = (a == 0x00);
	}

	void SetZf(Byte operand)
	{
		zf = (operand == 0x00);
	}

	void SetPf()
	{
		pf = true;
		for (int i = 0; i < 8; ++i)
		{
			if ((a >> i) & 1)
				pf = !pf;
		}
	}

	void SetPf(Byte operand)
	{
		pf = true;
		for (int i = 0; i < 8; ++i)
		{
			if ((operand >> i) & 1)
				pf = !pf;
		}
	}

	void SetCarryDueToSub(Byte operand)
	{
		cf = (a < operand);
	}

	void SetCarryDueToAdd(Byte operand)
	{
		Byte sum = a + operand;
		cf = (sum < a);
	}

	void SetAuxCarryDueToAdd(Byte operand)
	{
		af = (((a & 0x0f) + (operand & 0x0f)) > 0x09);
	}

	void SetAuxCarryDueToAdd(Byte operand1, Byte operand2)
	{
		af = (((operand1 & 0x0f) + (operand2 & 0x0f)) > 0x09);
	}

	void SetAuxCarryDueToSub(Byte operand)
	{
		af = ((a & 0x0f) < (operand & 0x0f));
	}

	void SetAuxCarryDueToSub(Byte operand1, Byte operand2)
	{
		af = ((operand1 & 0x0f) < (operand2 & 0x0f));
	}

	void SetAuxCarryDueToAnd(Byte operand)
	{
		af = (((a & 0x08) | (operand & 0x08)) == 0x08);
	}

	Memory& GetM()
	{
		size_t index = (h << 8) + l;
		return m[index];
	}

	Memory& GetST() // stack top
	{
		size_t index = sp;
		return m[index];
	}

	// registers
	Byte a;
	Byte b;
	Byte c;
	Byte d;
	Byte e;
	Byte h;
	Byte l;
	Address pc;
	Address parentBlockPc;
	Address sp;

	// condition flags
	bool cf;
	bool sf;
	bool zf;
	bool pf;
	bool af;

	// interrupt flag
	bool ie;
	
	// memory
	Memory* m;

	// interrupted
	bool isInterrupted;
	InterruptType interruptType;

	// compiler
	int resumeFromRecordIndex;
	int sideExitIndex;

	//benchmarking
	int* interpretedCount;
	int* nativelyExecutedCount;
};

#endif