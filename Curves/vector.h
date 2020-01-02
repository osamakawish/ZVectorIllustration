#ifndef VECTOR_H
#define VECTOR_H

#include <QAbstractGraphicsShapeItem>

class Node;

class Vector : public QAbstractGraphicsShapeItem {
    QPointF Head, Tail;
    void paintArrowHead(QPainter *p);

public:
    Vector(QPointF Head, Node *node=nullptr, QGraphicsItem *parent=nullptr);
    Vector(QPointF Head, QPointF Tail, QGraphicsItem *parent=nullptr);

    QPointF head(); QPointF tail();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // VECTOR_H
