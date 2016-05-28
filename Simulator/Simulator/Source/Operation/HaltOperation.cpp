#include "HaltOperation.h"

HaltOperation::HaltOperation(State * s, Address address, const OperationMetadata & metadata, NoOperandProcessorFunction function) :
	Operation(s, address, metadata),
	function_(function),
	outgoingEdges_()
{
}

std::unique_ptr<OutgoingEdges> HaltOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new NoneOutgoingEdges(outgoingEdges_));
}

void HaltOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void HaltOperation::Run()
{
	function_(s_);
}
