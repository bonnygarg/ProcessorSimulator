#ifndef _OPERATION_H_
#define _OPERATION_H_

#include <memory>
#include <State\State.h>
#include "Metadata\OperationMetadata.h"
#include "OutgoingEdges\OutgoingEdges.h"
#include <Global\Global.h>

#include <llvm\IR\Module.h>
#include <llvm\IR\IRBuilder.h>
#include <llvm\IR\Value.h>

class Operation
{
public:
	Operation(State* s, Address address, const OperationMetadata& metadata);
	virtual void Run() = 0;
	virtual void EmitCompiledCode(llvm::IRBuilder<>& irb, llvm::Value* statePointer, llvm::Module* module) = 0;
	virtual std::unique_ptr<OutgoingEdges> GetOutgoingEdges() = 0;
	const OperationMetadata& GetMetadata();
protected:
	State* s_;
	Address address_;
	const OperationMetadata& metadata_;
};

#endif