#include "RestartOperations.h"

RestartOperation::RestartOperation(State * s, Address address, const OperationMetadata & metadata, NoOperandProcessorFunction function, Address callAddress) :
	Operation(s, address, metadata),
	function_(function),
	outgoingEdges_(callAddress, address + 1)
{}

std::unique_ptr<OutgoingEdges> RestartOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new UnconditionalCallOutgoingEdges(outgoingEdges_));
}

void RestartOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void RestartOperation::Run()
{
	function_(s_);
}
