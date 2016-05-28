#ifndef _PROCESSOR_FUNCTION_POINTERS_H_
#define _PROCESSOR_FUNCTION_POINTERS_H_

#include <Global\Global.h>

class State;

typedef void(*NoOperandProcessorFunction)(State* s);
typedef void(*ByteOperandProcessorFunction)(State* s, Byte operand);
typedef void(*WordOperandProcessorFunction)(State* s, Word operand);

#endif