#ifndef _RESTART_OPERATION_H_
#define _RESTART_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\UnconditionalCallOutgoingEdges.h>

// Operations of type 'RST'
class RestartOperation : public Operation
{
public:
	RestartOperation(State*s, Address address, const OperationMetadata& metadata, NoOperandProcessorFunction function, Address callAddress);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	NoOperandProcessorFunction function_;
	UnconditionalCallOutgoingEdges outgoingEdges_;
};

#endif