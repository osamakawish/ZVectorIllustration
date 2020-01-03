#include "../graphicsview.h"
#include "curve.h"

#include <QPainter>
#include <QVector>

void Vector::paintArrowHead(QPainter *p)
{
    double arrowSize = 16; double headWidth = 4; double headLength = 14;

    QLineF head0 = QLineF(Head, Tail); head0.setLength(arrowSize);
    QLineF line = QLineF(head0.p2(),head0.p1());
    QLineF head1 = QLineF(head0); head1.setLength(headLength);
    QLineF perp0 = line.normalVector(); perp0.setLength(headWidth);
    QPointF diff = perp0.p2() - perp0.p1();

    QPointF p1 = Head; QPointF p3 = head1.p2();
    QPointF q2 = perp0.p2(); QPointF q4 = perp0.p1() - diff;

    const QVector<QPointF> points = {p1, q2, p3, q4};
    QPolygonF polygon(points);

    p->drawPolygon(polygon);
}

Vector::Vector(QPointF head, Node *node, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
  , Head(head) , Tail(node->point())
{}

Vector::Vector(QPointF head, QPointF tail, QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent) ,
    Head(head), Tail(tail)
{}

QPointF Vector::head()
{ return Head; }

QPointF Vector::tail()
{ return Tail; }

void Vector::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brush = painter->brush(); painter->setBrush(QColor(196,0,0,200));
    QPen pen = painter->pen(); painter->setPen(Qt::black);

    painter->drawLine(QPointF(),Head); paintArrowHead(painter);

    painter->setBrush(brush); painter->setPen(pen);
}

QRectF Vector::boundingRect() const
{
    qreal edge = pen().width() / 2; QPointF e(edge,edge);
    QRectF rect0(GraphicsView::rectangle(Head,Tail));
    QRectF rect1(rect0.topLeft()-2*e,rect0.bottomRight()+2*e); rect1.moveTopLeft(QPointF());

    return rect1;
}
