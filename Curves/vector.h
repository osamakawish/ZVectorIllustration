#ifndef VECTOR_H
#define VECTOR_H

#include <QAbstractGraphicsShapeItem>

class Node;

class Vector : public QAbstractGraphicsShapeItem {
    QPointF Tail, Head; QPointF P3; QPolygonF ArrowHead;
    double ArrowSize = 16; double HeadWidth = 4; double HeadLength = 14;
    void paintArrowHead(QPainter *p); void updateArrow();

public:
    Vector(Node *node, QPointF Head, QGraphicsItem *parent=nullptr);
    Vector(QPointF Tail, QPointF Head, QGraphicsItem *parent=nullptr);

    void head(QPointF head); void tail(QPointF tail);
    void moveTailWithFixedHead(QPointF newTail);
    QPointF head(); QPointF tail();
    QPolygonF arrowHead(); bool arrowHeadContains(QPointF pt);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // VECTOR_H
