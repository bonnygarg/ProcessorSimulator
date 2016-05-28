#include "NonCompilableOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

NonCompilableOutgoingEdges::NonCompilableOutgoingEdges(Address nonCompilableNextAddress) :
	nonCompilableNextAddress_(nonCompilableNextAddress)
{
}

Address NonCompilableOutgoingEdges::GetNonCompilableNextAddress() const
{
	return nonCompilableNextAddress_;
}

void NonCompilableOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
