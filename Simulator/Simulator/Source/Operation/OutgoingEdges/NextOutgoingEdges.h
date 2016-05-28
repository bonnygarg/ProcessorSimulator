#ifndef _NEXT_OUTGOING_EDGES_H_
#define _NEXT_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class NextOutgoingEdges : public OutgoingEdges
{
public:
	NextOutgoingEdges(Address nextAddress);
	Address GetNextAddress() const;
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address nextAddress_;
};


#endif