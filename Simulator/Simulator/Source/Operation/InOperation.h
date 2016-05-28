#ifndef _IN_OPERATION_H_
#define _IN_OPERATION_H_

#include <memory>
#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\NonCompilableOutgoingEdges.h>
#include <IO\IoBridge.h>

// Operations of type 'IN_OPCODE BYTE'
class InOperation : public Operation
{
public:
	InOperation(State*s, Address address, const OperationMetadata& metadata, const IoBridge& ioBridge);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	Byte operand_;
	NonCompilableOutgoingEdges outgoingEdges_;
	const IoBridge& ioBridge_;
};

#endif