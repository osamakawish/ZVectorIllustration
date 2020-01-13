#include "graphicsitem.h"

#include <QColor>

GraphicsItem::GraphicsItem(QGraphicsItem *parent) : QAbstractGraphicsShapeItem(parent)
{
    setFlags(GraphicsItemFlag::ItemIsMovable | GraphicsItemFlag::ItemIsSelectable);
    QPen p(pen()); p.setCosmetic(true); setPen(p);
}

GraphicsItem::~GraphicsItem()
{}

void GraphicsItem::setSelectedColoring(ColorFunc brushChange)
{
    UponSelection.BrushColor = brushChange(Original.brush().color());
}

void GraphicsItem::setSelectedColoring(ColorFunc penChange, ColorFunc brushChange)
{
    UponSelection.PenColor = penChange(Original.pen().color());
    UponSelection.BrushColor = brushChange(Original.brush().color());
}

QPen Coloring::pen()
{ return QPen(PenColor); }

QBrush Coloring::brush()
{ return QBrush(BrushColor); }
