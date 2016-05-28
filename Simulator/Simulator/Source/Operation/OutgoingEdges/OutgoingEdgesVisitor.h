#ifndef _OUTGOING_EDGES_VISITOR_H_
#define _OUTGOING_EDGES_VISITOR_H_

class UnconditionalJumpOutgoingEdges;
class ConditionalJumpOutgoingEdges;
class UnconditionalCallOutgoingEdges;
class ConditionalCallOutgoingEdges;
class UnconditionalReturnOutgoingEdges;
class ConditionalReturnOutgoingEdges;
class NextOutgoingEdges;
class NonCompilableOutgoingEdges;
class NoneOutgoingEdges;

class OutgoingEdgesVisitor
{
public:
	virtual void Visit(UnconditionalJumpOutgoingEdges& og) = 0;
	virtual void Visit(ConditionalJumpOutgoingEdges& og) = 0;
	virtual void Visit(UnconditionalCallOutgoingEdges& og) = 0;
	virtual void Visit(ConditionalCallOutgoingEdges& og) = 0;
	virtual void Visit(UnconditionalReturnOutgoingEdges& og) = 0;
	virtual void Visit(ConditionalReturnOutgoingEdges& og) = 0;
	virtual void Visit(NextOutgoingEdges& og) = 0;
	virtual void Visit(NonCompilableOutgoingEdges& og) = 0;
	virtual void Visit(NoneOutgoingEdges& og) = 0;
};

#endif