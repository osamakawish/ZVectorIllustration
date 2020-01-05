#include "curve.h"

#include <QPainter>

const qreal Node::nodeRadius = 6;


Node::Node(QPointF p, class Curve *curve, QGraphicsItem *parent) :  QAbstractGraphicsShapeItem(parent),
    Point(p), Curve(curve), In(new Vector(this,this->point())), Out(new Vector(this,this->point()))
{setPos(p);}

Node::~Node()
{ delete In; delete Out; delete Curve; }

QPointF Node::point()
{ return Point; }

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
