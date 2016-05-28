#ifndef _CONDITIONAL_RETURN_OPERATION_H_
#define _CONDITIONAL_RETURN_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\ConditionalReturnOutgoingEdges.h>

// Operations of type 'RETURN_OPCODE WORD'
class ConditionalReturnOperation : public Operation
{
public:
	ConditionalReturnOperation(State*s, Address address, const OperationMetadata& metadata, NoOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	NoOperandProcessorFunction function_;
	ConditionalReturnOutgoingEdges outgoingEdges_;
};

#endif