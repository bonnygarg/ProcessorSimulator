#include "CompiledBlock.h"

CompiledBlock::CompiledBlock(State * s, CompiledCode compiledCode) :
	s_(s),
	compiledCode_(compiledCode)
{}

void CompiledBlock::Run()
{
	s_->resumeFromRecordIndex = 0;
	while (s_->resumeFromRecordIndex != -1)
	{
		auto compilationUnit = compiledCode_.GetCompilationUnitTable()[s_->resumeFromRecordIndex];
		compilationUnit->Run();
	}
}
