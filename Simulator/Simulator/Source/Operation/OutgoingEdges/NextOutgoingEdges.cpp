#include "NextOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

NextOutgoingEdges::NextOutgoingEdges(Address nextAddress) :
	nextAddress_(nextAddress)
{
}

Address NextOutgoingEdges::GetNextAddress() const
{
	return nextAddress_;
}

void NextOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
