#include "CompiledMethod.h"

CompiledMethod::CompiledMethod(State * s, CompiledCode compiledCode) :
	s_(s),
	compiledCode_(compiledCode)
{}

void CompiledMethod::Run()
{
	s_->resumeFromRecordIndex = 0;
	while (s_->resumeFromRecordIndex != -1)
	{
		auto compilationUnit = compiledCode_.GetCompilationUnitTable()[s_->resumeFromRecordIndex];
		compilationUnit->Run();
	}
}
