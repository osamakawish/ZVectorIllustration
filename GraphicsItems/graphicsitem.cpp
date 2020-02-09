#include "graphicsitem.h"

#include <QColor>

GraphicsItem::GraphicsItem(QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
{
    setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable);
    QPen p(pen()); p.setCosmetic(true); setPen(p);
}

void GraphicsItem::scale(QPointF factor)
{
    qreal p = pen().widthF()/2;
    QTransform transform; transform.scale(factor.x(),factor.y());
    setTransform(transform); update(boundingRect().adjusted(-p,-p,p,p));
}

GraphicsItem::~GraphicsItem() {}

Selectable::Selectable(QGraphicsItem *parent) : GraphicsItem(parent) {}

Selectable::~Selectable() {}

Drawable::Drawable(QGraphicsItem *parent) : GraphicsItem(parent) {}

Drawable::~Drawable() {}
