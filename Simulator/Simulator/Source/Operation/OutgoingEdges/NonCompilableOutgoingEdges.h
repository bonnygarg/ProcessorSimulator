#ifndef _NON_COMPILABLE_OUTGOING_EDGES_H_
#define _NON_COMPILABLE_OUTGOING_EDGES_H_

#include <Global\Global.h>

#include "OutgoingEdges.h"

class NonCompilableOutgoingEdges : public OutgoingEdges
{
public:
	NonCompilableOutgoingEdges(Address nonCompilableNextAddress);
	Address GetNonCompilableNextAddress() const;
	// Inherited via OutgoingEdges
	virtual void Accept(OutgoingEdgesVisitor & visitor) override;
private:
	Address nonCompilableNextAddress_;
};


#endif