#ifndef _CONDITIONAL_RETURN_OUTGOING_EDGES_H_
#define _CONDITIONAL_RETURN_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class ConditionalReturnOutgoingEdges : public OutgoingEdges
{
public:
	ConditionalReturnOutgoingEdges(Address returnNotTakenAddress);
	Address GetReturnNotTakenAddress() const;
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address returnNotTakenAddress_;
};


#endif