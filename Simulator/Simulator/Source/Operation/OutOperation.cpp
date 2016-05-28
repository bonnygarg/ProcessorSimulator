#include "OutOperation.h"

OutOperation::OutOperation(State* s, Address address, const OperationMetadata & metadata, const IoBridge& ioBridge) :
	Operation(s, address, metadata),
	operand_(s->m[address + 1].byte),
	outgoingEdges_(address + 2),
	ioBridge_(ioBridge)
{

}

std::unique_ptr<OutgoingEdges> OutOperation::GetOutgoingEdges()
{
	return std::unique_ptr<OutgoingEdges>(new NonCompilableOutgoingEdges(outgoingEdges_));
}

void OutOperation::EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value * statePointer, llvm::Module * module)
{
	// emit nothing
}

void OutOperation::Run()
{
	ioBridge_.Write(operand_, s_->a);
	s_->pc += 2;
}
