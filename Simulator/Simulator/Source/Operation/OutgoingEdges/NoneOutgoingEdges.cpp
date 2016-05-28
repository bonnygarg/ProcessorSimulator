#include "NoneOutgoingEdges.h"
#include "OutgoingEdgesVisitor.h"

NoneOutgoingEdges::NoneOutgoingEdges()
{
}

void NoneOutgoingEdges::Accept(OutgoingEdgesVisitor & visitor)
{
	visitor.Visit(*this);
}
