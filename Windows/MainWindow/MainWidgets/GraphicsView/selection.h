#ifndef SELECTION_H
#define SELECTION_H

#include <limits>

#include <QDebug>

#include <QSet>
#include <QGraphicsItemGroup>
#include <QGraphicsView>
#include <QGraphicsPathItem>

#include "GraphicsItems/Shapes/shape.h"
#include "GraphicsItems/Curves/curve.h"
#include "GraphicsItems/Curves/node.h"
#include "GraphicsItems/Curves/vector.h"

enum class FinalizeOption { S_ONLY, T_ONLY, BOTH };

template<class S, class T>
class Selection
{
    typedef void (Selection::*PathUpdate)(QPoint);
    typedef void (Selection::*Finalize)(QPoint);
    typedef void (Selection::*Gather)(QList<QGraphicsItem *>);

    QPoint start;
    PathUpdate PATH_DRAW;
    Finalize FINALIZE;
    QGraphicsScene *SCENE;

    void updateRect(QPoint pt) {QPainterPath path; path.addRect(QRect(start,pt)); PATH->setPath(path);}
    void updatePath(QPoint pt) {QPainterPath path = PATH->path(); path.lineTo(pt); PATH->setPath(path);}

    void closePath() {QPainterPath path = PATH->path(); path.closeSubpath(); PATH->setPath(path);}

    //! Called when mouse is released.
    void finalize_(QPoint pt)
    { closePath(); (this->*PATH_DRAW)(pt); auto items = SCENE->items(PATH->path()); gather(items); amendPath(); finalizePath(); }
    void finalize_S(QPoint pt)
    { closePath(); (this->*PATH_DRAW)(pt); auto items = SCENE->items(PATH->path()); gather(items,true,false); amendPath(); finalizePath(); }
    void finalize_T(QPoint pt)
    { closePath(); (this->*PATH_DRAW)(pt); auto items = SCENE->items(PATH->path()); gather(items,false); amendPath(); finalizePath(); }

protected:
    QSet<S *> S_ITEMS = {};
    QSet<T *> T_ITEMS = {};

    QPen PEN; QBrush BRUSH;

    // Selection Rectangle -> make this a path.
    QGraphicsPathItem *PATH;
    QGraphicsItemGroup *GROUP;

    virtual void selectS(S *item)=0;
    virtual void selectT(T *item)=0;

    template<class R> void select(R *item)
    {auto s = dynamic_cast<S *>(item); if (s) {selectS(s);}
    auto t = dynamic_cast<S *>(item); if (t) {selectT(t);}
    GROUP->addToGroup(item);}

    //! Only need to account for any unexpected changes into selection rect.
    //! Resizing when an item is added is not necessary.
    virtual void finalizePath() {}

    void setPathRect(QRectF rect) {QPainterPath path; path.addRect(rect); PATH->setPath(path);}

    template<class R> void insert(QSet<R *> &items, QGraphicsItem *item, qreal &z, bool condition)
    {
        if (!condition) {return;} R *r = dynamic_cast<R *>(item);
        if (r) { items.insert(r); GROUP->addToGroup(r); qreal Z = item->zValue(); if (Z > z) {z=Z;} }
    }

    //! Distributes items based on whether they are of type S or T.
    // Make sure to update z-value.
    void gather(QList<QGraphicsItem *> items, bool s=true, bool t=true)
    {
        qreal z = -std::numeric_limits<qreal>::max(); auto it = items.begin();
        while (it != items.end()) { insert<S>(S_ITEMS,*it,z,s); insert<T>(T_ITEMS,*it,z,t); it++; }
        GROUP->setZValue(z);
    }

    template<class R>
    static qreal zValue(R *item) {return dynamic_cast<QGraphicsItem *>(item)->zValue();}

public:

    //! A class for controlling selections and maintaining track for two of their distinct types.
    //! Must be declared after setting the scene for the view.
    Selection(QGraphicsView *view) : SCENE(view->scene())
    {
        PATH = new QGraphicsPathItem; GROUP = new QGraphicsItemGroup;
        SCENE->addItem(PATH); GROUP = SCENE->createItemGroup({}); PATH->hide();
        PATH->setZValue(std::numeric_limits<qreal>::max());
        PATH->setPen(PEN); PATH->setBrush(BRUSH);
        updateAsPath(); setFinalizeOption(FinalizeOption::BOTH);
    }
    virtual ~Selection() {delete PATH; SCENE->destroyItemGroup(GROUP);}

    void startPath(QPoint pt) {resetSelection(); PATH->show(); start=pt; PATH->setPen(PEN); PATH->setBrush(BRUSH);}
    void updateAsPath(bool update=false) {PATH_DRAW = (update) ? (&Selection::updatePath) : (&Selection::updateRect);}
    void updateSelection(QPoint pt) {(this->*PATH_DRAW)(pt);}

    void setFinalizeOption(FinalizeOption fOption)
    {
        switch (fOption) {
        case FinalizeOption::S_ONLY: FINALIZE = &Selection::finalize_S; return;
        case FinalizeOption::T_ONLY: FINALIZE = &Selection::finalize_T; return;
        case FinalizeOption::BOTH:   FINALIZE = &Selection::finalize_; return;
        }
    }
    void finalize(QPoint pt) {(this->*FINALIZE)(pt);}

    // May want to hide from public
    QSet<S *> sItems() {return S_ITEMS;}
    QSet<T *> tItems() {return T_ITEMS;}

    // public // Note: Problems occur when drawing path after reselecting nothing.
    void resetSelection() {PATH->setPath(QPainterPath()); resetGroup(); updateAsPath();}
    void resetGroup() {SCENE->destroyItemGroup(GROUP); GROUP = SCENE->createItemGroup({});}
    void resetPath() {PATH->setPath(QPainterPath()); PATH->hide();}
    void amendPath()
    { if (GROUP->childItems().isEmpty()) {resetSelection();} else {setPathRect(GROUP->boundingRect());}}

    // public
    void clearS()
    { foreach (auto item, S_ITEMS) {if (GROUP->childItems().contains(item)) GROUP->removeFromGroup(item);} S_ITEMS.clear(); }
    void clearT()
    { foreach (auto item, T_ITEMS) {if (GROUP->childItems().contains(item)) GROUP->removeFromGroup(item);} T_ITEMS.clear(); }


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

    QString currentPathDraw() {
        if (PATH_DRAW == &Selection::updateRect) {return "updateRect";}
        if (PATH_DRAW == &Selection::updatePath) {return "updatePath";}
        return "2";
    }

    QString currentFinalize() {
        if (FINALIZE == &Selection::finalize_) { return "finalize_"; }
        if (FINALIZE == &Selection::finalize_S) { return "finalize_S"; }
        if (FINALIZE == &Selection::finalize_T) { return "finalize_T"; }
        return "8";
    }
};


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
