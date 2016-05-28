#include "ConditionalReturnOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

ConditionalReturnOutgoingEdges::ConditionalReturnOutgoingEdges(Address returnNotTakenAddress) :
	returnNotTakenAddress_(returnNotTakenAddress)
{
}

Address ConditionalReturnOutgoingEdges::GetReturnNotTakenAddress() const
{
	return returnNotTakenAddress_;
}

void ConditionalReturnOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
