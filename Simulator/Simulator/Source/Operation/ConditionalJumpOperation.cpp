#include "ConditionalJumpOperation.h"

ConditionalJumpOperation::ConditionalJumpOperation(State * s, Address address, const OperationMetadata & metadata, WordOperandProcessorFunction function) :
	Operation(s, address, metadata),
	operand_(s->m[address + 1].byte + (s->m[address + 2].byte * 256)),
	function_(function),
	outgoingEdges_(operand_, address + 3)
{

}

std::unique_ptr<OutgoingEdges> ConditionalJumpOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new ConditionalJumpOutgoingEdges(outgoingEdges_));
}

void ConditionalJumpOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	llvm::ConstantInt* operandArgument = llvm::ConstantInt::get(module->getContext(), llvm::APInt(16, operand_));

	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	argVector.push_back(operandArgument);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void ConditionalJumpOperation::Run()
{
	function_(s_, operand_);
}
