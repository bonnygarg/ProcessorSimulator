#include "ByteOperandOperation.h"

ByteOperandOperation::ByteOperandOperation(State* s, Address address, const OperationMetadata & metadata, ByteOperandProcessorFunction function) :
	Operation(s, address, metadata),
	operand_(s->m[address + 1].byte),
	function_(function),
	outgoingEdges_(address + 2)
{
	
}

std::unique_ptr<OutgoingEdges> ByteOperandOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new NextOutgoingEdges(outgoingEdges_));
}

void ByteOperandOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module)
{
	llvm::ConstantInt* operandArgument = llvm::ConstantInt::get(module->getContext(), llvm::APInt(8, operand_));

	std::vector<llvm::Value*> argVector;
	argVector.push_back(statePointer);
	argVector.push_back(operandArgument);
	llvm::ArrayRef<llvm::Value*> argArrayRef(argVector);

	llvm::Function* callee = module->getFunction(metadata_.GetFunctionName());

	irb.CreateCall(callee, argArrayRef);
}

void ByteOperandOperation::Run()
{
	function_(s_, operand_);
}
