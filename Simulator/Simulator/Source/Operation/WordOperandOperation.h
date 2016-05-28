#ifndef _WORD_OPERAND_OPERATION_H_
#define _WORD_OPERAND_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\NextOutgoingEdges.h>

// Operations of type 'OPCODE WORD'
class WordOperandOperation : public Operation
{
public:
	WordOperandOperation(State*s, Address address, const OperationMetadata& metadata, WordOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	Word operand_;
	WordOperandProcessorFunction function_;
	NextOutgoingEdges outgoingEdges_;
};

#endif