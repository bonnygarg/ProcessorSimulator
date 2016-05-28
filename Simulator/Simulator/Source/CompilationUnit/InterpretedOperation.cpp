#include "InterpretedOperation.h"

InterpretedOperation::InterpretedOperation(State* s, const NonCompilableOperationRecord nonCompilableOperationRecord, int resumeFromRecordIndex) :
	s_(s),
	nonCompilableOperationRecord_(nonCompilableOperationRecord),
	resumeFromRecordIndex_(resumeFromRecordIndex)
{}

void InterpretedOperation::Run()
{
	nonCompilableOperationRecord_.GetOperation()->Run();
	s_->resumeFromRecordIndex = resumeFromRecordIndex_;
}
