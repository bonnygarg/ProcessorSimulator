#ifndef _UNCONDITIONAL_JUMP_OUTGOING_EDGES_H_
#define _UNCONDITIONAL_JUMP_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class UnconditionalJumpOutgoingEdges : public OutgoingEdges
{
public:
	UnconditionalJumpOutgoingEdges(Address jumpAddress);
	Address GetJumpAddress() const;
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address jumpAddress_;
};


#endif