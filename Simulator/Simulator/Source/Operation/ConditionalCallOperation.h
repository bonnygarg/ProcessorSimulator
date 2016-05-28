#ifndef _CONDITIONAL_CALL_OPERATION_H_
#define _CONDITIONAL_CALL_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\ConditionalCallOutgoingEdges.h>

// Operations of type 'CALL_OPCODE WORD'
class ConditionalCallOperation : public Operation
{
public:
	ConditionalCallOperation(State*s, Address address, const OperationMetadata& metadata, WordOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	Word operand_;
	WordOperandProcessorFunction function_;
	ConditionalCallOutgoingEdges outgoingEdges_;
};

#endif