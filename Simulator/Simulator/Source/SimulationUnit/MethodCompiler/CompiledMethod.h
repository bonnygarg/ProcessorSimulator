#ifndef _COMPILED_METHOD_H_
#define _COMPILED_METHOD_H_

#include <unordered_map>

#include <Global\Global.h>
#include <SimulationUnit\SimulationUnit.h>
#include <State\State.h>
#include <Compiler\CompiledCode.h>

class CompiledMethod : public SimulationUnit
{
public:
	CompiledMethod(State* s, CompiledCode compiledCode);
	void Run() override;
private:
	State* s_;
	CompiledCode compiledCode_;
};

#endif