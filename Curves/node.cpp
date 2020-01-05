#include "curve.h"

#include <QPainter>

const qreal Node::nodeRadius = 6;


Node::Node(QPointF p, class Curve *curve, QGraphicsItem *parent) :  QAbstractGraphicsShapeItem(parent),
    Point(p), Curve(curve), In(new Vector(this,this->point())), Out(new Vector(this,this->point()))
{setPos(p);}

Node::~Node()
{ delete In; delete Out; delete Curve; }

//! Creates a copy of a node at this point to initiate a new curve.
//! Use this when the node is not a tail (first or last) node of the curve.
class Curve *Node::copy()
{ return new class Curve(Point,scene(),parentItem()); }

QPointF Node::point()
{ return Point; }

void Node::move(QPointF pt)
{ setPos(pt); In->setPos(pt); Out->setPos(pt); }

void Node::hide()
{ QAbstractGraphicsShapeItem::hide(); In->hide(); Out->hide(); }

void Node::hideVectors()
{ In->hide(); Out->hide(); }

void Node::showVectors()
{ In->show(); Out->show(); }

Vector *Node::inVector()
{ return In; }

Vector *Node::outVector()
{ return Out; }

void Node::inVector(QPointF head)
{ In->head(head); }

void Node::outVector(QPointF head)
{ Out->head(head); }

Node *Node::previousNode()
{ return Curve->Nodes.at(this).first; }

Node *Node::nextNode()
{ return Curve->Nodes.at(this).first; }

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{ painter->drawEllipse(-nodeRadius,-nodeRadius,2*nodeRadius,2*nodeRadius); }

QRectF Node::boundingRect() const
{ return QRectF(-nodeRadius-pen().widthF(),-nodeRadius-pen().widthF(),
                2*nodeRadius+pen().widthF(),2*nodeRadius+pen().widthF()); }
