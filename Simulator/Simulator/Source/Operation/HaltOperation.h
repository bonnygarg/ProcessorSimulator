#ifndef _HALT_OPERATION_H_
#define _HALT_OPERATION_H_

#include "Operation.h"
#include "OperationFunctionPointers.h"
#include "Operation\OutgoingEdges\NoneOutgoingEdges.h"

class HaltOperation : public Operation
{
public:
	HaltOperation(State*s, Address address, const OperationMetadata& metadata, NoOperandProcessorFunction function);

	// Inherited via PcrOperation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	NoOperandProcessorFunction function_;
	NoneOutgoingEdges outgoingEdges_;
};

#endif