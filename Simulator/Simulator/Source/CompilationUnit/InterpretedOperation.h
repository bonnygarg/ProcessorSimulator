#ifndef _INTERPRETED_OPERATION_H_
#define _INTERPRETED_OPERATION_H_

#include <memory>

#include <State\State.h>
#include "CompilationUnit.h"
#include <Cfg\NonCompilableOperationRecord.h>

class InterpretedOperation : public CompilationUnit
{
public:
	InterpretedOperation(State* s, const NonCompilableOperationRecord nonCompilableOperationRecord, int resumeFromRecordIndex);
	// inherited from CompilationUnit
	void Run() override;
private:
	State* s_;
	NonCompilableOperationRecord nonCompilableOperationRecord_;
	int resumeFromRecordIndex_;
};

#endif