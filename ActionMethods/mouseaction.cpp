
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

// Resetting the selection rect has bugs.
void MouseAction::shapePress(QMouseEvent *)
{
    // Want to show transform buttons when the selection is shown.
    if (!SHAPE_CURVE_SELECTION->setTransform(Mouse::pos()))
    {
        SHAPE_CURVE_SELECTION->updateAsPath(); SHAPE_CURVE_SELECTION->startPath(Mouse::pos());
    }
}

void MouseAction::shapeDoubleClick(QMouseEvent *)
{
    SHAPE_CURVE_SELECTION->updateAsPath(true); SHAPE_CURVE_SELECTION->startPath(Mouse::pos());
}

void MouseAction::shapeMove(QMouseEvent *)
{
    if (Mouse::isPressed())
    {
        if (SHAPE_CURVE_SELECTION->shouldTransform())
        {SHAPE_CURVE_SELECTION->transform(Mouse::movedBy(),Mouse::moved());}
        else
        {SHAPE_CURVE_SELECTION->updateSelection(Mouse::moved());}
    }
}

void MouseAction::shapeRelease(QMouseEvent *)
{
    // Bugs occur in case where nothing is selected after moving a selected object.
    // Need to figure out what happens to selection rect.
    if (SHAPE_CURVE_SELECTION->shouldTransform())// Need to reset transform option in this case.
    {SHAPE_CURVE_SELECTION->transform(Mouse::movedBy(),Mouse::moved());}
    else // When nothing is selected, selection should hide buttons.
    {SHAPE_CURVE_SELECTION->finalize(Mouse::releasePos()); }
}

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
    NODE_VECTOR_SELECTION->updateAsPath(); NODE_VECTOR_SELECTION->startPath(Mouse::pos());
}

void MouseAction::vectorDoubleClick(QMouseEvent *)
{
    NODE_VECTOR_SELECTION->setFinalizeOption(FinalizeOption::T_ONLY);
    NODE_VECTOR_SELECTION->startPath(Mouse::pos());
}

void MouseAction::vectorMove(QMouseEvent *)
{
    if (Mouse::isPressed())
    { NODE_VECTOR_SELECTION->updateSelection(Mouse::moved()); }
}

void MouseAction::vectorRelease(QMouseEvent *)
{
    NODE_VECTOR_SELECTION->finalize(Mouse::releasePos());
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











