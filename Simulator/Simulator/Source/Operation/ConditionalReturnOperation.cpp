#include "ConditionalReturnOperation.h"

ConditionalReturnOperation::ConditionalReturnOperation(State * s, Address address, const OperationMetadata & metadata, NoOperandProcessorFunction function) :
	Operation(s, address, metadata),
	function_(function),
	outgoingEdges_(address + 3)
{

}

std::unique_ptr<OutgoingEdges> ConditionalReturnOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new ConditionalReturnOutgoingEdges(outgoingEdges_));
}

void ConditionalReturnOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void ConditionalReturnOperation::Run()
{
	function_(s_);
}
