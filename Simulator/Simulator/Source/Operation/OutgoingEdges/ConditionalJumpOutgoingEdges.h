#ifndef _CONDITIONAL_JUMP_OUTGOING_EDGES_H_
#define _CONDITIONAL_JUMP_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class ConditionalJumpOutgoingEdges : public OutgoingEdges
{
public:
	ConditionalJumpOutgoingEdges(Address jumpTakenAddress, Address jumpNotTakenAddress);
	Address GetJumpTakenAddress() const;
	Address GetJumpNotTakenAddress() const;
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address jumpTakenAddress_;
	Address jumpNotTakenAddress_;
};


#endif