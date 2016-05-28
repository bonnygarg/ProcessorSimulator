#include "UnconditionalJumpOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

UnconditionalJumpOutgoingEdges::UnconditionalJumpOutgoingEdges(Address jumpAddress) :
	jumpAddress_(jumpAddress)
{
}

void UnconditionalJumpOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}

Address UnconditionalJumpOutgoingEdges::GetJumpAddress() const
{
	return jumpAddress_;
}
