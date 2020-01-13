#include "../../Windows/MainWindow/MainWidgets/graphicsview.h"
#include "curve.h"

#include <QPainter>
#include <QVector>
#include <QDebug>

void Vector::paintArrowHead(QPainter *p)
{ p->drawPolygon(ArrowHead); }

void Vector::updateArrow()
{
    prepareGeometryChange();
    QRectF before = boundingRect();

    QLineF head0 = QLineF(Head, Tail); head0.setLength(ArrowSize);
    QLineF line = QLineF(head0.p2(),head0.p1());
    QLineF head1 = QLineF(head0); head1.setLength(HeadLength);
    QLineF perp0 = line.normalVector(); perp0.setLength(HeadWidth);
    QPointF diff = perp0.p2() - perp0.p1();

    QPointF p1 = Head - Tail; QPointF p3 = head1.p2() - Tail; P3 = p3;
    QPointF q2 = perp0.p2() - Tail; QPointF q4 = perp0.p1() - diff - Tail;

    ArrowHead = QVector<QPointF> {p1, q2, p3, q4};

    QRectF after = boundingRect();
    update(before | after);
}

Vector::Vector(Node *node, QPointF head, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
  , Tail(node->point()), Head(head)
{setPos(Tail); updateArrow();}

Vector::Vector(QPointF tail, QPointF head, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
  , Tail(tail), Head(head)
{setPos(Tail); updateArrow();}

void Vector::head(QPointF head)
{ Head = head; updateArrow(); }

//! Moves tail without moving head. Use setPos to move the entire arrow.
void Vector::tail(QPointF tail)
{
    QPointF diff = tail - Tail;
    setPos(tail); Head = Head - diff;
    updateArrow();
}

QPointF Vector::head()
{ return Head; }

QPointF Vector::tail()
{ return Tail; }

QPolygonF Vector::arrowHead()
{ return ArrowHead; }

bool Vector::arrowHeadContains(QPointF pt)
{ return ArrowHead.containsPoint(pt,Qt::FillRule::WindingFill); }

void Vector::select()
{

}

void Vector::deselect()
{

}

void Vector::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brush = painter->brush(); painter->setBrush(QColor(0,0,196,128));
    QPen pen = painter->pen(); painter->setPen(Qt::black);

    paintArrowHead(painter);
    painter->drawLine(QPointF(),P3);

    painter->setBrush(brush); painter->setPen(pen);
}

QRectF Vector::boundingRect() const
{

    return GraphicsView::rectangle(Head-Tail,QPointF());
}
