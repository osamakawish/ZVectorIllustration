#ifndef MOUSEACTION_H
#define MOUSEACTION_H

#include <memory>
#include <type_traits>

#include <QSet>
#include <QPainterPath>

#include "mousebehaviour.h"
#include "../GraphicsItems/graphicsitem.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../Windows/MainWindow/MainWidgets/graphicsview.h"

class QPainterPath; class QMouseEvent; class QPointF;
class MainWindow; class QWidget; class QObject; class QGraphicsRectItem;
class Node; class Vector;

class MouseAction
{
    static QSet<Vector *> VectorsSelected;
    static QSet<Node *> NodesSelected;
    static QSet<Curve *> CurvesSelected;
    static void updateSelectionPath(QPointF p1, QPointF p2);
    static QGraphicsRectItem *selectionRect();
    static MainWindow *getMainWindow(QObject *w);

//    template<typename T>
    static void press();
    static void move();
    template<typename S, typename T>
    static void release(QSet<T *> &set)
    {
        if (!std::is_base_of<S,T>::value) {return;}
        updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::scenePos());

        auto view = MouseBehaviour::view(); view->select<S>(selectionRect()->rect());
        auto items = view->selectedItems();

        if (items.isEmpty()) { view->deselect(); set = {}; selectionRect()->hide(); }
        else { foreach (auto item, items) { T *t = dynamic_cast<T *>(item); if (t) {set.insert(t);} } }
    }

public:
    static void shapePress(QMouseEvent *e);
    static void shapeDoubleClick(QMouseEvent *e);
    static void shapeMove(QMouseEvent *e);
    static void shapeRelease(QMouseEvent *e);
    static void shapeToggle(bool toggle);

    static void resetCurve();
    static void vectorPress(QMouseEvent *e);
    static void vectorDoubleClick(QMouseEvent *e);
    static void vectorMove(QMouseEvent *e);
    static void vectorRelease(QMouseEvent *e);
    static void vectorToggle(bool toggle);
};

#endif // MOUSEACTION_H
