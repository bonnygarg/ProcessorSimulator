#ifndef _COMPILED_FUNCTION_H_
#define _COMPILED_FUNCTION_H_

#include <string>

#include "CompilationUnit.h"
#include <State\State.h>

#include <llvm\ExecutionEngine\ExecutionEngine.h>


class CompiledFunction : public CompilationUnit
{
public:
	typedef void(*CompiledFunctionType)(State*);
	CompiledFunction(State* s, llvm::ExecutionEngine* executionEngine, const std::string& functionName);
	~CompiledFunction();
	// inherited from CompilationUnit
	void Run() override;
private:
	State* s_;
	llvm::ExecutionEngine* executionEngine_;
	const std::string functionName_;
};

#endif