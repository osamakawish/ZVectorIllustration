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

Vector::Vector(Node *node, QPointF head, QGraphicsItem *parent) : Selectable(parent)
  , Tail(node->point()), Head(head)
{setPos(Tail); updateArrow();}

Vector::Vector(QPointF tail, QPointF head, QGraphicsItem *parent) : Selectable(parent)
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

bool Vector::arrowHeadContains(QPointF scenePt)
{ return ArrowHead.containsPoint(mapFromScene(scenePt),Qt::FillRule::WindingFill); }

void Vector::select()
{ Brush.setColor(QColor(64,64,196)); qreal w = Pen.widthF() / 2; update(ArrowHead.boundingRect().adjusted(-w,-w,w,w)); }

void Vector::deselect()
{ Brush.setColor(QColor(64,64,255)); qreal w = Pen.widthF() / 2; update(ArrowHead.boundingRect().adjusted(-w,-w,w,w)); }

void Vector::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brush = painter->brush(); painter->setBrush(Brush);
    QPen pen = painter->pen(); painter->setPen(Pen);

    paintArrowHead(painter);
    painter->drawLine(QPointF(),P3);
}

QRectF Vector::boundingRect() const
{ return GraphicsView::rectangle(Head,QPointF()); }
