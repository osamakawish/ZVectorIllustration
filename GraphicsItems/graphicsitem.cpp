#include "graphicsitem.h"

#include <QColor>

GraphicsItem::GraphicsItem(QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
{
    setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable);
    QPen p(pen()); p.setCosmetic(true); setPen(p);
}

GraphicsItem::~GraphicsItem() {}

Selectable::Selectable(QGraphicsItem *parent) : GraphicsItem(parent) {}

Selectable::~Selectable() {}

Drawable::Drawable(QGraphicsItem *parent) : GraphicsItem(parent) {}

Drawable::~Drawable() {}
