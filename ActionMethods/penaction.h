#ifndef PENACTION_H
#define PENACTION_H

#include <QGraphicsItemGroup>
#include <memory>

class QMouseEvent;

class PenAction
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

#endif // PENACTION_H
