#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QPen>
#include <QBrush>
#include <QColor>
#include <functional>
#include <QAbstractGraphicsShapeItem>

typedef std::function<QColor(QColor)> ColorFunc;

struct Coloring {
    QColor PenColor, BrushColor;

    QPen pen(); QBrush brush();
};

class GraphicsItem : public QAbstractGraphicsShapeItem
{
    bool isSelected();
    Coloring Original, UponSelection;

public:
    GraphicsItem(QGraphicsItem *parent=nullptr);
    virtual ~GraphicsItem();

    void select();
    void deselect();

    //! Choose how pen and brush colors change upon selection;
    void setSelectedColoring(ColorFunc brushChange);
    void setSelectedColoring(ColorFunc penChange, ColorFunc brushChange);
};

class Drawable : GraphicsItem {
public:
    Drawable(QGraphicsItem *parent=nullptr);
    virtual ~Drawable();


};

class Shape : Drawable {

};

#endif // GRAPHICSITEM_H
