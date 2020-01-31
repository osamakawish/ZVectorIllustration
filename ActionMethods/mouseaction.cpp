
#include <QMouseEvent>
#include <QDebug>

#include "mouseaction.h"
#include "../Windows/MainWindow/MainWidgets/GraphicsView/graphicsview.h"
#include "mousebehaviour.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../GraphicsItems/graphicsitem.h"
#include "../Windows/MainWindow/mainwindow.h"

SelectionNodeVector &MouseAction::selectionNodeVector()
{ return Mouse::view()->NODE_VECTOR_SELECTION; }

SelectionShapeCurve &MouseAction::selectionShapeCurve()
{ return Mouse::view()->SHAPE_CURVE_SELECTION; }

// Return earliest parent that's a mainwindow.
MainWindow *MouseAction::getMainWindow(QObject *w)
{
    QObject *parent = w->parent();
    MainWindow *window = dynamic_cast<MainWindow *>(parent);

    return (window) ? (window) : (getMainWindow(parent));
}

void MouseAction::shapePress(QMouseEvent *)
{

}

void MouseAction::shapeDoubleClick(QMouseEvent *)
{

}

void MouseAction::shapeMove(QMouseEvent *)
{

}

void MouseAction::shapeRelease(QMouseEvent *)
{ }

void MouseAction::shapeToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::PRESS = &MouseAction::shapePress;
        GraphicsView::DOUBLE_CLICK = &MouseAction::shapeDoubleClick;
        GraphicsView::MOVE = &MouseAction::shapeMove;
        GraphicsView::RELEASE = &MouseAction::shapeRelease;
    }
    else {

    }
}

void MouseAction::vectorPress(QMouseEvent *)
{

}

void MouseAction::vectorDoubleClick(QMouseEvent *)
{
}

void MouseAction::vectorMove(QMouseEvent *)
{

}

void MouseAction::vectorRelease(QMouseEvent *)
{

}

void MouseAction::vectorToggle(bool toggle)
{
    auto curvesSelected = Mouse::view()->SHAPE_CURVE_SELECTION.tItems();
    if (toggle) {
        // If no curve is selected, switch to shape mouse
        if (curvesSelected.size() == 0)
        {getMainWindow(Mouse::view())->graphicsActionGroup.actions().first()->trigger(); return;}

        foreach (Curve *curve, curvesSelected) { curve->showNodes(); }
        GraphicsView::PRESS = &MouseAction::vectorPress;
        GraphicsView::DOUBLE_CLICK = &MouseAction::vectorDoubleClick;
        GraphicsView::MOVE = &MouseAction::vectorMove;
        GraphicsView::RELEASE = &MouseAction::vectorRelease;
    }
    else {
        foreach (Curve *curve, curvesSelected) { curve->hideNodes(); }
        curvesSelected = {};
    }
}











