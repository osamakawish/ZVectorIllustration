#ifndef MOUSEACTION_H
#define MOUSEACTION_H

#include <memory>
#include <type_traits>

#include <QSet>
#include <QPainterPath>

#include "mousebehaviour.h"
#include "../GraphicsItems/graphicsitem.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../Windows/MainWindow/MainWidgets/GraphicsView/graphicsview.h"

class QPainterPath; class QMouseEvent; class QPointF;
class MainWindow; class QWidget; class QObject; class QGraphicsRectItem;
class Node; class Vector; class FileWidget;

namespace {
template<class S, class T>
bool is_same() {return std::is_same<S,T>::value;}
}

class MouseAction
{
    static SelectionNodeVector *NODE_VECTOR_SELECTION;
    static SelectionShapeCurve *SHAPE_CURVE_SELECTION;
    friend class FileWidget;

    static MainWindow *getMainWindow(QObject *w);

public:
    static void shapePress(QMouseEvent *e);
    static void shapeDoubleClick(QMouseEvent *e);
    static void shapeMove(QMouseEvent *e);
    static void shapeRelease(QMouseEvent *e);
    static void shapeToggle(bool toggle);

    static void vectorPress(QMouseEvent *e);
    static void vectorDoubleClick(QMouseEvent *e);
    static void vectorMove(QMouseEvent *e);
    static void vectorRelease(QMouseEvent *e);
    static void vectorToggle(bool toggle);
};

#endif // MOUSEACTION_H
