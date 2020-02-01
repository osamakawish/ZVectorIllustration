
#include <QMouseEvent>
#include <QDebug>

#include "mouseaction.h"
#include "../Windows/MainWindow/MainWidgets/GraphicsView/graphicsview.h"
#include "mousebehaviour.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../GraphicsItems/graphicsitem.h"
#include "../Windows/MainWindow/mainwindow.h"
#include "Windows/MainWindow/MainWidgets/GraphicsView/selection.h"

// Changes in FileWidget::tabChange
SelectionNodeVector *MouseAction::NODE_VECTOR_SELECTION = nullptr;
SelectionShapeCurve *MouseAction::SHAPE_CURVE_SELECTION = nullptr;

//! Return earliest parent that's a mainwindow.
MainWindow *MouseAction::getMainWindow(QObject *w)
{
    QObject *parent = w->parent();
    MainWindow *window = dynamic_cast<MainWindow *>(parent);

    return (window) ? (window) : (getMainWindow(parent));
}

void MouseAction::shapePress(QMouseEvent *)
{ SHAPE_CURVE_SELECTION->startPath(Mouse::pos().toPoint()); SHAPE_CURVE_SELECTION->updateAsPath(); }

void MouseAction::shapeDoubleClick(QMouseEvent *)
{ SHAPE_CURVE_SELECTION->updateAsPath(true); }

void MouseAction::shapeMove(QMouseEvent *)
{
    if (Mouse::isPressed())
    {SHAPE_CURVE_SELECTION->updateSelection(Mouse::moved().toPoint());}
}

void MouseAction::shapeRelease(QMouseEvent *)
{ SHAPE_CURVE_SELECTION->finalize(Mouse::releasePos().toPoint());  }

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
    NODE_VECTOR_SELECTION->startPath(Mouse::pos().toPoint()); NODE_VECTOR_SELECTION->updateAsPath();
}

void MouseAction::vectorDoubleClick(QMouseEvent *)
{
    NODE_VECTOR_SELECTION->setFinalizeOption(FinalizeOption::T_ONLY);
}

void MouseAction::vectorMove(QMouseEvent *)
{
    if (Mouse::isPressed())
    { NODE_VECTOR_SELECTION->updateSelection(Mouse::moved().toPoint()); }
}

void MouseAction::vectorRelease(QMouseEvent *)
{
    NODE_VECTOR_SELECTION->finalize(Mouse::releasePos().toPoint());
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











