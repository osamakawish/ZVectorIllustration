#ifndef SHAPE_H
#define SHAPE_H

#include "../graphicsitem.h"

class Shape : public Drawable {
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    QPen PEN; QBrush BRUSH;

public:
    Shape(QGraphicsItem *parent=nullptr);

    void setPen(QPen);
    void setBrush(QBrush);

    virtual void paint(QPainter *painter)=0;
    virtual ~Shape();
};

class Ellipse : public Shape {
    qreal w=0, h=0;

public:
    Ellipse(QGraphicsItem *parent=nullptr);
    Ellipse(const QRectF &rect, QGraphicsItem *parent = nullptr);
    Ellipse(qreal w, qreal h, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    ~Ellipse();

    void paint(QPainter *painter) override;
    QRectF boundingRect() const override;

    operator QGraphicsEllipseItem *();
};

#endif // SHAPE_H
