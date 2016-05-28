#include "InOperation.h"

InOperation::InOperation(State* s, Address address, const OperationMetadata & metadata, const IoBridge& ioBridge) :
	Operation(s, address, metadata),
	operand_(s->m[address + 1].byte),
	outgoingEdges_(address + 2),
	ioBridge_(ioBridge)
{

}

std::unique_ptr<OutgoingEdges> InOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new NonCompilableOutgoingEdges(outgoingEdges_));
}

void InOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	// emit nothing
}

void InOperation::Run()
{
	s_->a = ioBridge_.Read(operand_);
	s_->pc += 2;
}
