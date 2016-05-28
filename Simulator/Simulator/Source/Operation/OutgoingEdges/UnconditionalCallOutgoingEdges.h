#ifndef _UNCONDITIONAL_CALL_OUTGOING_EDGES_H_
#define _UNCONDITIONAL_CALL_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class UnconditionalCallOutgoingEdges : public OutgoingEdges
{
public:
	UnconditionalCallOutgoingEdges(Address callTakenAddress, Address callNotTakenAddress);
	Address GetCallTakenAddress() const;
	Address GetCallNotTakenAddress() const; // return address
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address callTakenAddress_;
	Address callNotTakenAddress_;
};


#endif