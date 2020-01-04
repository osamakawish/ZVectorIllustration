#ifndef VECTOR_H
#define VECTOR_H

#include <QAbstractGraphicsShapeItem>

class Node;

class Vector : public QAbstractGraphicsShapeItem {
    QPointF Tail, Head; QPointF P3;
    double ArrowSize = 16; double HeadWidth = 4; double HeadLength = 14;
    void paintArrowHead(QPainter *p);

public:
    Vector(Node *node, QPointF Head, QGraphicsItem *parent=nullptr);
    Vector(QPointF Tail, QPointF Head, QGraphicsItem *parent=nullptr);

    QPointF head(); QPointF tail();
    QPolygonF arrowHead();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // VECTOR_H
