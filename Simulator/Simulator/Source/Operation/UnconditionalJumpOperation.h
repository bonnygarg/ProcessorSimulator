#ifndef _UNCONDITIONAL_JUMP_OPERATION_H_
#define _UNCONDITIONAL_JUMP_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\UnconditionalJumpOutgoingEdges.h>

// Operations of type 'JUMP_OPCODE WORD'
class UnconditionalJumpOperation : public Operation
{
public:
	UnconditionalJumpOperation(State*s, Address address, const OperationMetadata& metadata, WordOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	Word operand_;
	WordOperandProcessorFunction function_;
	UnconditionalJumpOutgoingEdges outgoingEdges_;
};

#endif