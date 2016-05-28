#include "NoOperandOperation.h"

NoOperandOperation::NoOperandOperation(State * s, Address address, const OperationMetadata & metadata, NoOperandProcessorFunction function) : 
	Operation(s, address, metadata),
	function_(function),
	outgoingEdges_(address + 1)
{
}

std::unique_ptr<OutgoingEdges> NoOperandOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new NextOutgoingEdges(outgoingEdges_));
}

void NoOperandOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void NoOperandOperation::Run()
{
	function_(s_);
}
