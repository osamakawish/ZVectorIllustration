#ifndef NODE_H
#define NODE_H

#include <QAbstractGraphicsShapeItem>
#include <memory>
#include "vector.h"

class Curve;

// Need to figure out how I'm going to do this.
class Node : public QAbstractGraphicsShapeItem {
    QPointF Point; Curve *Curve; Vector *In, *Out;

public:
    Node(QPointF p, class Curve *curve, QGraphicsItem *parent=nullptr);
    ~Node();

    QPointF point();

    Vector *inVector(); Vector *outVector();
    Vector *inVector(QPointF tail); Vector *outVector(QPointF head);

    Node *previousNode();
    Node *nextNode();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    static const qreal nodeRadius;
};

#endif // NODE_H
