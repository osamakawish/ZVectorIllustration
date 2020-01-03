#include "curve.h"

#include <QPainter>

const qreal Node::nodeRadius = 6;


Node::Node(QPointF p, class Curve *curve, QGraphicsItem *parent) :  QAbstractGraphicsShapeItem(parent),
    Point(p), Curve(curve), In(new Vector(this->point(),this)), Out(new Vector(this->point(),this))
{setPos(p);}

Node::~Node()
{ delete In; delete Out; delete Curve; }

QPointF Node::point()
{ return Point; }

Vector *Node::inVector()
{ return In; }

Vector *Node::outVector()
{ return Out; }

/*  Note: For the inVector and outVector setters, change the vectors themselves.
 *  The current code is for testing purposes.
 */
//! head: The arrow head.
Vector *Node::inVector(QPointF head)
{
    if (In) delete In;
    In = new Vector(head,this,parentItem());
    return In;
}

Vector *Node::outVector(QPointF head)
{
    if (Out) delete Out;
    Out = new Vector(head,this,parentItem());
    return Out;
}

Node *Node::previousNode()
{ return Curve->Nodes.at(this).first; }

Node *Node::nextNode()
{ return Curve->Nodes.at(this).first; }

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{ painter->drawEllipse(-nodeRadius,-nodeRadius,2*nodeRadius,2*nodeRadius); }

QRectF Node::boundingRect() const
{ return QRectF(-nodeRadius-pen().widthF(),-nodeRadius-pen().widthF(),
                2*nodeRadius+pen().widthF(),2*nodeRadius+pen().widthF()); }
