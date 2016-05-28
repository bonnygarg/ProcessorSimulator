#ifndef _WORD_OPERAND_OPERATION_FACTORY_H_
#define _WORD_OPERAND_OPERATION_FACTORY_H_

#include "OperationFactory.h"
#include <Operation\WordOperandOperation.h>

class WordOperandOperationFactory : public OperationFactory
{
public:
	WordOperandOperationFactory(const OperationMetadata& metadata, WordOperandProcessorFunction function);
	// Inherited via OperationFactory
	std::unique_ptr<Operation> CreateOperation(State* s, Address address);
private:
	WordOperandProcessorFunction function_;
};

#endif