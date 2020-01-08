#ifndef PENACTION_H
#define PENACTION_H

#include <QGraphicsItemGroup>
#include <memory>

class QMouseEvent; class Curve; class Node;

//! @class PenAction
//! For mouse events involving the pen shape and vector tools.
//!
//! @note (For Devs: Vector Cases)
//! Deal with the following cases:
//! (1) First time creating a curve (no curve selected)
//! (2) Adding points to a selected curve
//! (3) Starting a new point from middle of another curve
//! (4) Snapping to a node on a curve

class PenAction
{
    static Curve *CurrentCurve;
    static bool OnFirstPoint;

    static void updatePreviewPath();
    static void updateCurrentNode();

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

#endif // PENACTION_H
