#ifndef SELECTION_H
#define SELECTION_H

#include <limits>

#include <QDebug>

#include <QSet>
#include <QGraphicsItem>
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
    // For selecting objects
    typedef void (Selection::*PathUpdate)(QPointF);
    typedef void (Selection::*Finalize)(QPointF);
    typedef void (Selection::*Gather)(QList<QGraphicsItem *>);

    void updateRect(QPointF pt) {QPainterPath path; path.addRect(QRectF(START,pt)); PATH->setPath(path);}
    void updatePath(QPointF pt) {QPainterPath path = PATH->path(); path.lineTo(pt); PATH->setPath(path);}

    void closePath() {QPainterPath path = PATH->path(); path.closeSubpath(); PATH->setPath(path);}

    //! Called when mouse is released.
    // Need to hide selection buttons when deselecting.
    void finalize_(QPointF pt)
    { closePath(); (this->*PATH_DRAW)(pt); auto items = SCENE->items(PATH->path()); gather(items); amendPath(); }
    void finalize_S(QPointF pt)
    { closePath(); (this->*PATH_DRAW)(pt); auto items = SCENE->items(PATH->path()); gather(items,true,false); amendPath(); }
    void finalize_T(QPointF pt)
    { closePath(); (this->*PATH_DRAW)(pt); auto items = SCENE->items(PATH->path()); gather(items,false); amendPath(); }



protected:
    QPointF START;
    PathUpdate PATH_DRAW;
    Finalize FINALIZE;
    QGraphicsScene *SCENE;

    QSet<S *> S_ITEMS = {};
    QSet<T *> T_ITEMS = {};

    QPen PEN; QBrush BRUSH;

    // Selection Rectangle -> make this a path.
    QGraphicsPathItem *PATH;
    QGraphicsItemGroup *GROUP;

    virtual void select(S *item)=0;
    virtual void select(T *item)=0;
    //! Called when everything is to be deselected.
    virtual void deselect()=0;

    //! Only need to account for any unexpected changes into selection rect.
    //! Resizing when an item is added is not necessary.
    virtual void finalizePath() {}

    void setPathRect(QRectF rect) {QPainterPath path; path.addRect(rect); PATH->setPath(path);}

    template<class R> void insert(QSet<R *> &items, QGraphicsItem *item, qreal &z, bool condition)
    {
        if (!condition) {return;} R *r = dynamic_cast<R *>(item);
        if (r) { items.insert(r); GROUP->addToGroup(r); select(r); qreal Z = item->zValue(); if (Z > z) {z=Z;} }
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

    void virtual moveBy(QPointF df, QPointF) {GROUP->moveBy(df.x(),df.y()); PATH->moveBy(df.x(),df.y());}

public:

    //! A class for controlling selections and maintaining track for two of their distinct types.
    //! Must be declared after setting the scene for the view.
    Selection(QGraphicsView *view) : SCENE(view->scene())
    {
        resetPath(false); PATH->hide();
        GROUP = new QGraphicsItemGroup; GROUP = SCENE->createItemGroup({});
        updateAsPath(); setFinalizeOption(FinalizeOption::BOTH);
    }

    virtual ~Selection() {delete PATH; SCENE->destroyItemGroup(GROUP);}

    // Selection does reset. But path still has issues. Path start point is not cursor start point in buggy scenario.
    void startPath(QPointF pt) {resetSelection(); PATH->show(); START=pt; PATH->setPen(PEN); PATH->setBrush(BRUSH);}
    void updateAsPath(bool update=false) {PATH_DRAW = (update) ? (&Selection::updatePath) : (&Selection::updateRect);}
    void updateSelection(QPointF pt) {(this->*PATH_DRAW)(pt);}

    void setFinalizeOption(FinalizeOption fOption)
    {
        switch (fOption) {
        case FinalizeOption::S_ONLY: FINALIZE = &Selection::finalize_S; return;
        case FinalizeOption::T_ONLY: FINALIZE = &Selection::finalize_T; return;
        case FinalizeOption::BOTH:   FINALIZE = &Selection::finalize_; return;
        }
    }
    void finalize(QPointF pt) {(this->*FINALIZE)(pt);}

    // May want to hide from public
    QSet<S *> sItems() {return S_ITEMS;}
    QSet<T *> tItems() {return T_ITEMS;}

    // Want optional behaviour for deselecting objects.
    void resetSelection() {resetPath(); resetGroup(); updateAsPath();}
    void resetGroup() {SCENE->destroyItemGroup(GROUP); GROUP = SCENE->createItemGroup({});}
    void resetPath(bool del=true)
    {
        if (del) {delete PATH;}
        PATH = new QGraphicsPathItem;
        SCENE->addItem(PATH);
        PATH->setZValue(std::numeric_limits<qreal>::max()-1);
        PATH->setPen(PEN); PATH->setBrush(BRUSH);
        PATH->setPath(QPainterPath());
    }

    void amendPath()
    {
        if (GROUP->childItems().isEmpty()) { deselect(); PATH->hide(); resetSelection(); }
        else {setPathRect(GROUP->boundingRect()); finalizePath(); }
    }

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
};


class SelectionNodeVector : public Selection<Node, Vector>
{
public:
    SelectionNodeVector(QGraphicsView *view);
    ~SelectionNodeVector();

    void select(Node *item) override;
    void select(Vector *item) override;
    void deselect() override;

protected:
    void finalizePath() override;
};

class SelectionShapeCurve : public Selection<Shape, Curve>
{
    static QRectF SCALE_BUTTON_RECT;
    static QRectF MOVE_BUTTON_RECT;

    QPointF MVP = QPointF();

    QTransform TRANSFORM_APPLIED = QTransform();
    QPointF TRANSFORMATION_ORIGIN;

    // For applying transformations on selection
    // Should first initialize them, then draw them when the selection rect is drawn.
    typedef void (SelectionShapeCurve::*Transform)(QPointF, QPointF);
    typedef QGraphicsPathItem TransformButton;
    QMap<TransformButton *,QPointF> SCALE_BUTTONS;
    TransformButton *MOVE_BUTTON;
    TransformButton *SELECTED_BUTTON;
    Transform TRANSFORM_BY;

    TransformButton *getTransformButton(QPointF pt);
    void setTransformOrigin(QGraphicsPathItem *pt);
    void resetTransformButtons();
    void initializeScaleButtons();

    void applyTransformation();
    QPointF rectBoundaryPoint(QPointF relativePos, QRectF rect);

    QRectF selectionBoundingRect();
    TransformButton *getAcrossScaleButton(TransformButton *button);

    void resizeToRect(QRectF rect);
    void scaleTransform(QPointF df);

    //! Call when mouse is released.
    //! Reset translation and replace it with a new pos()
    //! Alternatively, may want to try to get the new sclae button position based on the transformation applied.


public:
    SelectionShapeCurve(QGraphicsView *view);
    ~SelectionShapeCurve();

    void select(Shape *item) override;
    void select(Curve *item) override;

    void showNodes();
    void showButtons(bool visible);

    // True if item is to be transformed, and prepares transformation, false otherwise.
    // Transforms if the item clicks a transform button.
    bool shouldTransform();
    bool setTransform(QPointF pt);
    void transform(QPointF df, QPointF pt);
    void endTransform();

protected:
    void deselect() override;
    void rescaleBy(QPointF df, QPointF);
//    void shearBy(QPointF df, QPointF); -> Need to work on this a little
    void moveBy(QPointF df, QPointF) override;
    void finalizePath() override;
private:
    QPointF scaleFactors(QPointF df, QSizeF size);
};

#endif // SELECTION_H
