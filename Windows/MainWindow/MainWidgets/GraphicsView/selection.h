#ifndef SELECTION_H
#define SELECTION_H

#include <limits>

#include <QSet>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QGraphicsPathItem>

template<class S, class T>
class Selection
{
    QGraphicsScene *SCENE;

protected:
    QSet<S *> S_ITEMS = {};
    QSet<T *> T_ITEMS = {};

    // Selection Rectangle -> make this a path.
    QGraphicsPathItem *PATH;
    QGraphicsItemGroup *GROUP;

    void setRectPen(QColor pen) {PATH->setPen(pen);}
    void setRectBrush(QColor brush) {PATH->setBrush(brush);}

    virtual void selectS(S *item)=0;
    virtual void selectT(T *item)=0;

    template<class R> void select(R *item)
    {auto s = dynamic_cast<S *>(item); if (s) {selectS(s);}
    auto t = dynamic_cast<S *>(item); if (t) {selectT(t);}}

    void addAll(QSet<QGraphicsItem *> items)
    {
        auto it = items.begin();
        while (it != items.end())
        {
            if (dynamic_cast<S *>(*it)) {S_ITEMS.insert(*it);}
            else if (dynamic_cast<T *>(*it)) {T_ITEMS.insert(*it);}
            it++;
        }
    }

    //! Only need to account for any unexpected changes into selection rect.
    //! Resizing when an item is added is not necessary.
    virtual void finalizePath()=0;

    void setPathRect(QRectF rect) {QPainterPath path; path.addRect(rect); PATH->setPath(path);}

    void gatherItems(QList<QGraphicsItem *> items)
    {
        auto it = items.begin();
        while (it != items.end()) {
            S *s = dynamic_cast<S *>(*it); T *t = dynamic_cast<T *>(*it);
            if (s) { S_ITEMS.insert(s); GROUP->addToGroup(*it); }
            else if (t) { T_ITEMS.insert(t); GROUP->addToGroup(*it); }
            it++;
        }
        finalizePath();
    }

    template<class R>
    qreal zValue(R *item) {return dynamic_cast<QGraphicsItem *>(item)->zValue();}

public:
    //! A class for controlling selections and maintaining track for two of their distinct types.
    //! Must be declared after setting the scene for the view.
    Selection(QGraphicsView *view) : SCENE(view->scene())
    {
        PATH = new QGraphicsPathItem; GROUP = new QGraphicsItemGroup;
        SCENE->addItem(PATH); GROUP = SCENE->createItemGroup({}); PATH->hide();
        PATH->setZValue(std::numeric_limits<qreal>::max());
    }
    virtual ~Selection() {delete PATH; SCENE->destroyItemGroup(GROUP);}

    // Updates
    void finalizeRect(QRect rect)
    { setPathRect(rect); auto items = SCENE->items(rect); gatherItems(items); }
    void finalizeRect(QPoint p1, QPoint p2)
    { finalizeRect(QRect(p1,p2)); }
    void finalizePath(QPainterPath path)
    { PATH->setPath(path); auto items = SCENE->items(path); gatherItems(items); }

    //! Only resizes the rectangle.
    void setRect(QPointF p1, QPointF p2)
    { setRect(QRectF(p1,p2).toRect().normalized()); }
    void setRect(QRect rect)
    { setPathRect(rect); }
    void setPath(QPainterPath path)
    { setPath(path); }
    QGraphicsPathItem *path() {return PATH;}
    QGraphicsItemGroup *group() {return GROUP;}

    template<class R>
    void addItem(R *item)
    {
        S_ITEMS.insert(item); GROUP->addToGroup(item);
        setPathRect(GROUP->boundingRect()); select(item); finalizePath();
        qreal z = zValue(item); if (z > GROUP->zValue()) {GROUP->setZValue(z);}
    }

    void selectAll_S()
    { for (auto it=S_ITEMS.begin(); it!=S_ITEMS.end(); it++) { selectS(*it); } }
    void selectAll_T()
    { for (auto it=T_ITEMS.begin(); it!=T_ITEMS.end(); it++) { selectT(*it); } }

    QSet<S *> sItems() {return S_ITEMS;}
    QSet<T *> tItems() {return T_ITEMS;}

    void resetSelection() {resetRect(); resetGroup();}
    void resetGroup() {SCENE->destroyItemGroup(GROUP); GROUP = SCENE->createItemGroup({});}
    void resetRect() {setPathRect(QRect()); PATH->hide();}

    void clearS()
    { foreach (auto item, S_ITEMS) {if (GROUP->childItems().contains(item)) GROUP->removeFromGroup(item);} S_ITEMS.clear(); }
    void clearT()
    { foreach (auto item, T_ITEMS) {if (GROUP->childItems().contains(item)) GROUP->removeFromGroup(item);} T_ITEMS.clear(); }

    void showRect() {PATH->show();}

    static qreal minZValue(QList<QGraphicsItem *> items)
    {
        qreal min = std::numeric_limits<double>::max();
        foreach (auto item, items) { qreal n = item->zValue(); if (n < min) min = n; }
        return min;
    }

    static qreal maxZValue(QList<QGraphicsItem *> items)
    {
        qreal max = std::numeric_limits<double>::min();
        foreach (auto item, items) { qreal n = item->zValue(); if (n > max) max = n; }
        return max;
    }
};

class Node; class Vector;

// Need to clean code using this.
class SelectionNodeVector : public Selection<Node, Vector>
{
public:
    SelectionNodeVector(QGraphicsView *view);
    ~SelectionNodeVector();

    void selectS(Node *item) override;
    void selectT(Vector *item) override;

protected:
    void finalizePath() override;
};

class Shape; class Curve;

// Need to clean code using this.
class SelectionShapeCurve : public Selection<Shape, Curve>
{
public:
    SelectionShapeCurve(QGraphicsView *view);
    ~SelectionShapeCurve();

    void selectS(Shape *item) override;
    void selectT(Curve *item) override;

    void showNodes();

protected:
    void finalizePath() override;
};

#endif // SELECTION_H
