#include "ConditionalCallOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

ConditionalCallOutgoingEdges::ConditionalCallOutgoingEdges(Address callTakenAddress, Address callNotTakenAddress) :
	callTakenAddress_(callTakenAddress),
	callNotTakenAddress_(callNotTakenAddress)
{
}

Address ConditionalCallOutgoingEdges::GetCallTakenAddress() const
{
	return callTakenAddress_;
}

Address ConditionalCallOutgoingEdges::GetCallNotTakenAddress() const
{
	return callNotTakenAddress_;
}

void ConditionalCallOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
