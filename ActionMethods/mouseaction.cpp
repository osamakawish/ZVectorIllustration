
#include <QMouseEvent>
#include <QDebug>

#include "mouseaction.h"
#include "../Windows/MainWindow/MainWidgets/graphicsview.h"
#include "mousebehaviour.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../GraphicsItems/graphicsitem.h"
#include "../Windows/MainWindow/mainwindow.h"

QSet<Vector *> MouseAction::VectorsSelected = {};
QSet<Node *> MouseAction::NodesSelected = {};
QSet<Curve *> MouseAction::CurvesSelected = {};

void MouseAction::updateSelectionPath(QPointF p1, QPointF p2)
{
    QRectF rect = GraphicsView::rectangle(p1,p2);
    QPainterPath path = QPainterPath(); path.addRect(rect);
    selectionRect()->setRect(path.controlPointRect());
}

QGraphicsRectItem *MouseAction::selectionRect()
{ return MouseBehaviour::view()->selectionRect(); }

// Return earliest parent that's a mainwindow.
MainWindow *MouseAction::getMainWindow(QObject *w)
{
    QObject *parent = w->parent();
    MainWindow *window = dynamic_cast<MainWindow *>(parent);

    return (window) ? (window) : (getMainWindow(parent));
}

void MouseAction::press()
{
    auto view = MouseBehaviour::view(); QPointF pos = MouseBehaviour::pos();

    // If nothing selected or point outside selection rect, start new selection rect
    if (view->selectedItems().isEmpty() || !view->selectionRect()->contains(pos))
    { selectionRect()->show(); updateSelectionPath(pos,pos); }

    // Otherwise, prepare to move object (note:
    else {

    }
}

void MouseAction::move()
{
    if (!MouseBehaviour::isPressed()) {return;}
    updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::moved());
}

void MouseAction::shapePress(QMouseEvent *)
{ press(); }

void MouseAction::shapeDoubleClick(QMouseEvent *)
{

}

void MouseAction::shapeMove(QMouseEvent *)
{
    // If nothing selected, control cursor based on mouse position

    // If something is selected
    // .. if mouse click within selection, prepare to move

    // Otherwise, prepare selection rect.
    move();
}

void MouseAction::shapeRelease(QMouseEvent *)
{ release<Drawable>(CurvesSelected); } // If mouse was double clicked, switch action to mouseVector

void MouseAction::shapeToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::Press = &MouseAction::shapePress;
        GraphicsView::DoubleClick = &MouseAction::shapeDoubleClick;
        GraphicsView::Move = &MouseAction::shapeMove;
        GraphicsView::Release = &MouseAction::shapeRelease;
    }
    else {

    }
}

void MouseAction::vectorPress(QMouseEvent *)
{
    press();
    // Again, prepare a selection rectangle.

    // If intersects with a node, select it.

    // If nodes are selected, check if a vector is selected.
}

void MouseAction::vectorDoubleClick(QMouseEvent *e)
{
    // If clicked in the middle of a curve, add a node that doesn't change its shape by much
}

void MouseAction::vectorMove(QMouseEvent *e)
{
    move();
    // Node selection: move node

    // Vector selection
    // - move selected vector heads by diff in position of mouse
    // - if double clicked: all vectors have same relative position from their tails.
}

void MouseAction::vectorRelease(QMouseEvent *e)
{
    if (NodesSelected.isEmpty()) {release<Node>(NodesSelected); MouseBehaviour::view()->deselect();}
    else if (VectorsSelected.isEmpty()) {release<Vector>(VectorsSelected);}
    // Node selection: move node and select it.
    // - Single clicked on a node
    // - Double clicked in middle of curve

    // Vector selection: move vector
    // - Single clicked on a vector: single vector selected
    // - Double clicked before moving: groups of vectors selected

    // Deselect vector/node.
    // - Nothing in selection area of appropriate type
}

void MouseAction::vectorToggle(bool toggle)
{
    if (toggle) {
        // If no curve is selected, switch to shape mouse
        if (CurvesSelected.size() == 0)
        {getMainWindow(MouseBehaviour::view())->graphicsActionGroup.actions().first()->trigger(); return;}

        foreach (Curve *curve, CurvesSelected) { curve->showNodes(); }
        GraphicsView::Press = &MouseAction::vectorPress;
        GraphicsView::DoubleClick = &MouseAction::vectorDoubleClick;
        GraphicsView::Move = &MouseAction::vectorMove;
        GraphicsView::Release = &MouseAction::vectorRelease;
    }
    else {
        foreach (Curve *curve, CurvesSelected) { curve->hideNodes(); }
        CurvesSelected = {};
    }
}











