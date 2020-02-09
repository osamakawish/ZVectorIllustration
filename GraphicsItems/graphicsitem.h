#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QPen>
#include <QBrush>
#include <QColor>
#include <functional>
#include <QAbstractGraphicsShapeItem>

class GraphicsItem : public QAbstractGraphicsShapeItem
{
public:
    GraphicsItem(QGraphicsItem *parent=nullptr);

    void scale(QPointF factor);

    virtual ~GraphicsItem();
};

class Selectable : public GraphicsItem {
public:
    Selectable(QGraphicsItem *parent=nullptr);
    virtual ~Selectable();

    virtual void select()=0;
    virtual void deselect()=0;
};

class Drawable : public GraphicsItem {
public:
    Drawable(QGraphicsItem *parent=nullptr);
    virtual ~Drawable();
};

#endif // GRAPHICSITEM_H
