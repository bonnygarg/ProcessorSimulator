#include "UnconditionalCallOperation.h"

UnconditionalCallOperation::UnconditionalCallOperation(State * s, Address address, const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	Operation(s, address, metadata),
	operand_(s->m[address + 1].byte + (s->m[address + 2].byte * 256)),
	function_(function),
	outgoingEdges_(operand_, address + 3)
{

}

std::unique_ptr<OutgoingEdges> UnconditionalCallOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new UnconditionalCallOutgoingEdges(outgoingEdges_));
}

void UnconditionalCallOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	llvm::ConstantInt* operandArgument = llvm::ConstantInt::get(module->getContext(), llvm::APInt(16, operand_));

	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	argVector.push_back(operandArgument);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void UnconditionalCallOperation::Run()
{
	function_(s_, operand_);
}
