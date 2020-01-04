#include "../graphicsview.h"
#include "curve.h"

#include <QPainter>
#include <QVector>
#include <QDebug>

void Vector::paintArrowHead(QPainter *p)
{ p->drawPolygon(arrowHead()); }

Vector::Vector(Node *node, QPointF head, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
  , Tail(node->point()), Head(head)
{setPos(Tail);}

Vector::Vector(QPointF tail, QPointF head, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
  , Tail(tail), Head(head)
{setPos(Tail);}

QPointF Vector::head()
{ return Head; }

QPointF Vector::tail()
{ return Tail; }

QPolygonF Vector::arrowHead()
{
    QLineF head0 = QLineF(Head, Tail); head0.setLength(ArrowSize);
    QLineF line = QLineF(head0.p2(),head0.p1());
    QLineF head1 = QLineF(head0); head1.setLength(HeadLength);
    QLineF perp0 = line.normalVector(); perp0.setLength(HeadWidth);
    QPointF diff = perp0.p2() - perp0.p1();

    QPointF p1 = Head - Tail; QPointF p3 = head1.p2() - Tail; P3 = p3;
    QPointF q2 = perp0.p2() - Tail; QPointF q4 = perp0.p1() - diff - Tail;

    return QVector<QPointF> {p1, q2, p3, q4};;
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
    qreal edge = pen().width() / 2; QPointF e(edge,edge);
    QRectF rect0(GraphicsView::rectangle(Head,Tail));
    QRectF rect1(rect0.topLeft()-2*e,rect0.bottomRight()+2*e); rect1.moveTopLeft(QPointF());

    return rect1;
}
