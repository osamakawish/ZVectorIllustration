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
    Node(QPointF p, class Curve *curve=nullptr, QGraphicsItem *parent=nullptr);
    ~Node();

    class Curve *copy();
    QPointF point();

    void setScene(QGraphicsScene *scene);
    void move(QPointF pt); void hide();
    void hideVectors(); void showVectors();
    Vector *inVector(); Vector *outVector();
    void inVector(QPointF tail); void outVector(QPointF head);

    Node *previousNode();
    Node *nextNode();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;

    static const qreal nodeRadius;
};

#endif // NODE_H
