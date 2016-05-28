#ifndef _CONDITIONAL_JUMP_OPERATION_H_
#define _CONDITIONAL_JUMP_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\ConditionalJumpOutgoingEdges.h>

// Operations of type 'JUMP_OPCODE WORD'
class ConditionalJumpOperation : public Operation
{
public:
	ConditionalJumpOperation(State*s, Address address, const OperationMetadata& metadata, WordOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	Word operand_;
	WordOperandProcessorFunction function_;
	ConditionalJumpOutgoingEdges outgoingEdges_;
};

#endif