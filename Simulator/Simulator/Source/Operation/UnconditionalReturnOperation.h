#ifndef _UNCONDITIONAL_RETURN_OPERATION_H_
#define _UNCONDITIONAL_RETURN_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\UnconditionalReturnOutgoingEdges.h>

// Operations of type 'RETURN_OPCODE WORD'
class UnconditionalReturnOperation : public Operation
{
public:
	UnconditionalReturnOperation(State*s, Address address, const OperationMetadata& metadata, NoOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	NoOperandProcessorFunction function_;
	UnconditionalReturnOutgoingEdges outgoingEdges_;
};

#endif