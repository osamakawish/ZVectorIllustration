#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QAbstractGraphicsShapeItem>

class GraphicsItem : QAbstractGraphicsShapeItem
{
public:
    GraphicsItem(QGraphicsItem *parent=nullptr);
    virtual ~GraphicsItem();
};

#endif // GRAPHICSITEM_H
