#include "CompiledFunction.h"

CompiledFunction::CompiledFunction(State* s, llvm::ExecutionEngine* executionEngine, const std::string& functionName) :
	s_(s),
	executionEngine_(executionEngine),
	functionName_(functionName)
{}

CompiledFunction::~CompiledFunction()
{
	delete executionEngine_;
}

void CompiledFunction::Run()
{
	CompiledFunctionType function = (CompiledFunctionType)executionEngine_->getFunctionAddress(functionName_);
	function(s_);
}
