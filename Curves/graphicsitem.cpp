#include "graphicsitem.h"

#include <QPen>

GraphicsItem::GraphicsItem(QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
{
    setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable);
    QPen p(pen()); p.setCosmetic(true); setPen(p);
}

GraphicsItem::~GraphicsItem()
{

}
