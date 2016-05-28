#ifndef _INTERRUPT_TYPE_H_
#define _INTERRUPT_TYPE_H_

enum class InterruptType
{
	None,
	Halted,
	CodeModified,
	UnknownOpcode
};

#endif