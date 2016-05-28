#include "UnconditionalReturnOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

UnconditionalReturnOutgoingEdges::UnconditionalReturnOutgoingEdges()
{
}

void UnconditionalReturnOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
