#ifndef _NO_OPERAND_OPERATION_H_
#define _NO_OPERAND_OPERATION_H_

#include "Operation.h"
#include "OperationFunctionPointers.h"
#include "Operation\OutgoingEdges\NextOutgoingEdges.h"

// Operation of type 'OPCODE'
class NoOperandOperation : public Operation
{
public:
	NoOperandOperation(State*s, Address address, const OperationMetadata& metadata, NoOperandProcessorFunction function);

	// Inherited via PcrOperation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	NoOperandProcessorFunction function_;
	NextOutgoingEdges outgoingEdges_;
};

#endif