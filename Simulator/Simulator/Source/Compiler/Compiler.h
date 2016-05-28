#ifndef _COMPILER_H_
#define _COMPILER_H_

#include <unordered_map>
#include <memory>

#include <Global\Global.h>
#include <State\State.h>
#include <CompilationUnit\CompilationUnit.h>
#include <CompilationUnit\CompiledFunction.h>
#include <CompilationUnit\InterpretedOperation.h>
#include "CompiledCode.h"
#include <Cfg\Cfg.h>

#include <llvm\IR\Verifier.h>
#include <llvm\IR\LegacyPassManager.h>
#include <llvm\IR\PassManager.h>
#include <llvm\Transforms\Scalar.h>
#include <llvm\Transforms\IPO.h>
#include "llvm\ExecutionEngine\GenericValue.h"
#include <llvm\ExecutionEngine\MCJIT.h>
#include "llvm\IR\Constants.h"
#include "llvm\IR\DerivedTypes.h"
#include "llvm\IR\Instructions.h"
#include "llvm\IR\LLVMContext.h"
#include "llvm\IR\Module.h"
#include "llvm\Support\TargetSelect.h"
#include "llvm\Support\raw_ostream.h"
#include <llvm\IR\IRBuilder.h>
#include <llvm\IRReader\IRReader.h>
#include <llvm\Support\SourceMgr.h>
#include <llvm\Support\Debug.h>

class Compiler
{
public:
	Compiler(State* s);
	bool Compile(std::shared_ptr<Cfg> cfg, CompiledCode& compiledCode);
private:
	State* s_;
};

#endif