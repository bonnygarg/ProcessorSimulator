#ifndef _UNCONDITIONAL_RETURN_OUTGOING_EDGES_H_
#define _UNCONDITIONAL_RETURN_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class UnconditionalReturnOutgoingEdges : public OutgoingEdges
{
public:
	UnconditionalReturnOutgoingEdges();
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
};


#endif