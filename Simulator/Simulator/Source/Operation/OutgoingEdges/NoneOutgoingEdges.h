#ifndef _NONE_OUTGOING_EDGES_H_
#define _NONE_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class NoneOutgoingEdges : public OutgoingEdges
{
public:
	NoneOutgoingEdges();
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
};


#endif