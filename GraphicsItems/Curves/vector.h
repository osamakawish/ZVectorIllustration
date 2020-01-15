#ifndef VECTOR_H
#define VECTOR_H

#include <QPen>
#include <QBrush>
#include "../graphicsitem.h"

class Node;

class Vector : public Selectable {

    QPointF Tail, Head; QPointF P3; QPolygonF ArrowHead;
    double ArrowSize = 16; double HeadWidth = 4; double HeadLength = 14;
    QPen Pen = QPen(Qt::black); QBrush Brush = QBrush(QColor(64,64,255));

    void paintArrowHead(QPainter *p); void updateArrow();

public:
    Vector(Node *node, QPointF Head, QGraphicsItem *parent=nullptr);
    Vector(QPointF Tail, QPointF Head, QGraphicsItem *parent=nullptr);

    void head(QPointF head); void tail(QPointF tail);
    QPointF head(); QPointF tail();
    QPolygonF arrowHead(); bool arrowHeadContains(QPointF pt);

    void select() override;
    void deselect() override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // VECTOR_H
