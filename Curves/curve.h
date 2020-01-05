#ifndef CURVE_H
#define CURVE_H

#include <QGraphicsItemGroup>
#include <memory>
#include <unordered_map>
#include <utility>

#include "node.h"

class Curve : public QAbstractGraphicsShapeItem {
    std::unordered_map<Node *,std::pair<Node *, Node*>> Nodes;
    Node *First; Node *Last; Node *Selected;
    QPainterPath Path;

    void drawSegment(Node *current, Node *next);

    typedef std::pair<Node *, Node *> NodePair;

public:
    Curve(QPointF pt, QGraphicsScene *scene, QGraphicsItem *parent=nullptr);
    ~Curve();

    //! Adds a control point to the last node.
    Node *add(QPointF p);
    void remove(Node *pt);
    void close();

    void updatePath();

    void hideNodes(); void showNodes();
    void hideVectors(); void showVectors();
    void hideVectorsAndNodes(); void showVectorsAndNodes();

    void setParentItem(QGraphicsItem *item);

    void paint(QPainter *p, const QStyleOptionGraphicsItem *, QWidget *) override;
    QRectF boundingRect() const override;

    friend class Node;
};



#endif // CURVE_H
