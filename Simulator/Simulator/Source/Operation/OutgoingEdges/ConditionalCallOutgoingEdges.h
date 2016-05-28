#ifndef _CONDITIONAL_CALL_OUTGOING_EDGES_H_
#define _CONDITIONAL_CALL_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class ConditionalCallOutgoingEdges : public OutgoingEdges
{
public:
	ConditionalCallOutgoingEdges(Address callTakenAddress, Address callNotTakenAddress);
	Address GetCallTakenAddress() const;
	Address GetCallNotTakenAddress() const;
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address callTakenAddress_;
	Address callNotTakenAddress_;
};


#endif