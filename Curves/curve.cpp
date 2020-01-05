#include "curve.h"

#include <iostream>
#include <QDebug>
#include <QPainter>
#include <QGraphicsScene>

//! Draws curve segments while accounting for null cases.
//! Asserts current != 0 && next != 0.
void Curve::drawSegment(Node *current, Node *next)
{
    Vector *from = current->outVector(); Vector *to = next->inVector();
    QPointF c1, c2;

    c1 = (from) ? (from->head()) : (current->point());
    c2 = (to) ? (to->head()) : (next->point());

    Path.cubicTo( c1, c2, next->point() );
}

Curve::Curve(QPointF pt, QGraphicsScene *scene, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
{
    First = new Node(pt,this,parentItem()); Last = First; Selected = First; scene->addItem(this); scene->addItem(First);
    Nodes.insert( std::pair<Node *,NodePair>(First,NodePair(nullptr,nullptr)) );
}

Curve::~Curve()
{ delete First; delete Last; delete Selected; }

// Note: Must make sure that each Curve is a series of nodes (no node has more than one prev/next node).
// Better to allow tail nodes (First and Last) to be selectable but not others.
Node *Curve::add(QPointF p)
{
    Node *nd = new Node(p,this,parentItem()); scene()->addItem(nd); qDebug() << scene();
    Nodes.insert( std::pair<Node *,NodePair>(nd,NodePair(Selected,nullptr)) );
    Nodes.at(Selected).second = nd;

    Last = nd; Selected = nd;

    updatePath();
    return nd;
}

void Curve::remove(Node *nd)
{
    auto iter = Nodes.find(nd);
    Node *prev = (*iter).second.first; Node *next = (*iter).second.second;
    Nodes.at(prev).second = next; Nodes.at(next).first = prev;

    Nodes.erase(iter);
    updatePath();
}

Node *Curve::first()
{ return First; }

Node *Curve::last()
{ return Last; }

void Curve::updatePath()
{
    Node *current; current=First;
    Path = QPainterPath(current->point());
    Node *next = Nodes.at(current).second;

    while ((current != Last) && next) {
        drawSegment(current,next);
        current = next; next = Nodes.at(current).second;
    }
}

void Curve::hideNodes()
{ auto it = Nodes.begin(); while (it != Nodes.end()) { it->first->hide(); it++; } }

void Curve::showNodes()
{ auto it = Nodes.begin(); while (it != Nodes.end()) { it->first->show(); it++; } }

void Curve::hideVectors()
{

}

void Curve::showVectors()
{

}

void Curve::hideVectorsAndNodes()
{

}

void Curve::showVectorsAndNodes()
{

}

void Curve::setParentItem(QGraphicsItem *parent)
{
    QAbstractGraphicsShapeItem::setParentItem(parent);
    auto it = Nodes.begin(); while (it != Nodes.end()) { it->first->setParentItem(parent); it++; }
}

void Curve::paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *)
{ updatePath(); p->drawPath(Path); }

QRectF Curve::boundingRect() const
{
    QRectF beforeEdges = Path.boundingRect(); QPointF edgeDiff = QPointF(pen().widthF(),pen().widthF());
    return QRectF(beforeEdges.topLeft()-edgeDiff,beforeEdges.bottomRight()+edgeDiff);
}
