#ifndef _BYTE_OPERAND_OPERATION_H_
#define _BYTE_OPERAND_OPERATION_H_

#include "Operation.h"
#include <Operation\OperationFunctionPointers.h>
#include <Operation\OutgoingEdges\NextOutgoingEdges.h>

// Operations of type 'OPCODE BYTE'
class ByteOperandOperation : public Operation
{
public:
	ByteOperandOperation(State*s, Address address, const OperationMetadata& metadata, ByteOperandProcessorFunction function);

	// Inherited via Operation
	std::unique_ptr<OutgoingEdges> GetOutgoingEdges() override;
	void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) override;
	void Run() override;
private:
	Byte operand_;
	ByteOperandProcessorFunction function_;
	NextOutgoingEdges outgoingEdges_;
};

#endif