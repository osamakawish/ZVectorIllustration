#ifndef MOUSEACTION_H
#define MOUSEACTION_H

#include <QMouseEvent>

class GraphicsView;

class MouseAction
{
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
