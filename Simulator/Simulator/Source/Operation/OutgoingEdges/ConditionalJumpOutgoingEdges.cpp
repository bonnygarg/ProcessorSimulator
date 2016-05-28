#include "ConditionalJumpOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

ConditionalJumpOutgoingEdges::ConditionalJumpOutgoingEdges(Address jumpTakenAddress, Address jumpNotTakenAddress) :
	jumpTakenAddress_(jumpTakenAddress),
	jumpNotTakenAddress_(jumpNotTakenAddress)
{
}

Address ConditionalJumpOutgoingEdges::GetJumpTakenAddress() const
{
	return jumpTakenAddress_;
}

Address ConditionalJumpOutgoingEdges::GetJumpNotTakenAddress() const
{
	return jumpNotTakenAddress_;
}

void ConditionalJumpOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
