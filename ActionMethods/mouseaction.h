#ifndef MOUSEACTION_H
#define MOUSEACTION_H

#include <memory>
#include <QSet>

class GraphicsView; class QPainterPath; class QMouseEvent; class QPointF; class Curve;
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

    template<typename T>
    static void press(QMouseEvent *e, QSet<T> &selected);
    template<typename T>
    static void move(QMouseEvent *e, QSet<T> &selected);
    template<typename T>
    static void release(QMouseEvent *e, QSet<T> &selected);

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
