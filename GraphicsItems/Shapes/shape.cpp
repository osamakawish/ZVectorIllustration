#include "shape.h"

#include <QPainter>
#include <QGraphicsScene>

Shape::Shape(QGraphicsItem *parent) : Drawable(parent)
{}

Shape::~Shape()
{}

Ellipse::Ellipse(QGraphicsItem *parent) : Shape(parent)
{setPos(QPointF(0,0));}

Ellipse::Ellipse(const QRectF &rect, QGraphicsItem *parent) : Shape(parent)
{w=rect.width()/2; h=rect.height()/2; setPos(rect.center());}

Ellipse::Ellipse(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : Shape(parent),
    w(width/2), h(height/2)
{setPos(x+width/2,y+height/2);}

Ellipse::~Ellipse()
{}

void Ellipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{ painter->drawEllipse(QRectF(-w,-h,2*w,2*h).normalized()); }

QRectF Ellipse::boundingRect() const
{ qreal d=pen().widthF(); return QRectF(-w,-h,2*w,2*h).normalized().adjusted(-d,-d,d,d); }
