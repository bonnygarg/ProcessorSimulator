#include "UnconditionalCallOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

UnconditionalCallOutgoingEdges::UnconditionalCallOutgoingEdges(Address callTakenAddress, Address callNotTakenAddress) :
	callTakenAddress_(callTakenAddress),
	callNotTakenAddress_(callNotTakenAddress)
{
}

Address UnconditionalCallOutgoingEdges::GetCallTakenAddress() const
{
	return callTakenAddress_;
}

Address UnconditionalCallOutgoingEdges::GetCallNotTakenAddress() const
{
	return callNotTakenAddress_;
}

void UnconditionalCallOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}