#ifndef MOUSEACTION_H
#define MOUSEACTION_H

#include <memory>

class GraphicsView; class QPainterPath; class QMouseEvent; class QPointF;

class MouseAction
{
    static QPainterPath SelectionPath;

    static void updateSelectionPath(QPointF p1, QPointF p2);

public:
    static void shapePress(QMouseEvent *e);
    static void shapeDoubleClick(QMouseEvent *e);
    static void shapeMove(QMouseEvent *e);
    static void shapeRelease(QMouseEvent *e);

    static void vectorPress(QMouseEvent *e);
    static void vectorDoubleClick(QMouseEvent *e);
    static void vectorMove(QMouseEvent *e);
    static void vectorRelease(QMouseEvent *e);
};

#endif // MOUSEACTION_H
