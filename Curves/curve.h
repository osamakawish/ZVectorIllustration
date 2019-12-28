#ifndef CURVE_H
#define CURVE_H

#include <QGraphicsItemGroup>
#include <memory>

class Node;

class Arrow : public QAbstractGraphicsShapeItem {
    Arrow(Node tail, QPointF head, Node *parent=nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

class Curve;

class Node : public QAbstractGraphicsShapeItem {
    std::unique_ptr<QGraphicsEllipseItem> Shape;
    std::unique_ptr<Arrow> InArrow;
    std::unique_ptr<Arrow> OutArrow;

public:
    Node(QPointF p, Curve *parent=nullptr);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

class Curve : private QGraphicsItemGroup {

public:
    Curve(QGraphicsItem *parent=nullptr);

    //! Adds a control point to the last node.
    Node &add(QPointF p);
    void remove(Node &pt);
};



#endif // CURVE_H
