#ifndef _OUTGOING_EDGES_H_
#define _OUTGOING_EDGES_H_

class OutgoingEdgesVisitor;

class OutgoingEdges
{
public:
	virtual void Accept(OutgoingEdgesVisitor& visitor) = 0;
};

#endif