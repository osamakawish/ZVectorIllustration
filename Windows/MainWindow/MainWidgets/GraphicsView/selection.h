#ifndef SELECTION_H
#define SELECTION_H

#include <QSet>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QGraphicsRectItem>

template<class S, class T>
class Selection
{
    QGraphicsItemGroup *GROUP;
    QGraphicsScene *SCENE;

protected:
    QSet<S *> S_ITEMS = {};
    QSet<T *> T_ITEMS = {};

    // Selection Rectangle
    QGraphicsRectItem *RECT;

    void setRectPen(QColor pen) {RECT->setPen(pen);}
    void setRectBrush(QColor brush) {RECT->setBrush(brush);}

    virtual void selectS(S *item)=0;
    virtual void selectT(T *item)=0;

    //! Only need to account for any unexpected changes into selection rect.
    //! Resizing when an item is added is not necessary.
    virtual void updateSelectionRect()=0;

public:
    //! A class for controlling selections and maintaining track for two of their distinct types.
    //! Must be declared after setting the scene for the view.
    Selection(QGraphicsView *view)
        : SCENE(view->scene())
    {
        RECT = new QGraphicsRectItem; GROUP = new QGraphicsItemGroup;
        SCENE->addItem(RECT); SCENE->addItem(GROUP); RECT->hide();
    }
    virtual ~Selection() {}

    void setRect(QRect rect)
    {
        RECT->setRect(rect); auto items = SCENE->items(rect);

        auto it = items.begin();
        // Iterate over items and add them to group and appropriate set, if any.
        while (it != items.end())
        {
            S *s = dynamic_cast<S *>(*it); if (s) { S_ITEMS.insert(s); it++; }
            else { T *t = dynamic_cast<T *>(*it); if (t) {T_ITEMS.insert(t);} it++; }
        }
    }

    void setRect(QPointF p1, QPointF p2)
    { setRect(QRectF(p1,p2).toRect().normalized()); }

    void addItem(S *item)
    {S_ITEMS.insert(item); GROUP->addToGroup(item);
    RECT->setRect(GROUP->boundingRect()); selectS(item); updateSelectionRect();}
    void addItem(T *item)
    {T_ITEMS.insert(item); GROUP->addToGroup(item);
    RECT->setRect(GROUP->boundingRect()); selectT(item); updateSelectionRect();}

    QSet<S *> sItems() {return S_ITEMS;}
    QSet<T *> tItems() {return T_ITEMS;}

    void resetRect() {RECT->setRect(QRect());}
};

class Node; class Vector;

// Need to clean code using this.
class SelectionNodeVector : Selection<Node, Vector>
{
public:
    SelectionNodeVector(QGraphicsView *view);
    ~SelectionNodeVector();

    void selectS(Node *item) override;
    void selectT(Vector *item) override;

protected:
    void updateSelectionRect() override;
};

class Shape; class Curve;

// Need to clean code using this.
class SelectionShapeCurve : Selection<Shape, Curve>
{
public:
    SelectionShapeCurve(QGraphicsView *view);
    ~SelectionShapeCurve();

    void selectS(Shape *item) override;
    void selectT(Curve *item) override;

    void showNodes();

protected:
    void updateSelectionRect() override;
};

#endif // SELECTION_H
