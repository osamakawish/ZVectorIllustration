
#include <QMouseEvent>
#include <QDebug>

#include "mouseaction.h"
#include "graphicsview.h"
#include "mousebehaviour.h"
#include "Curves/curve.h"
#include "Curves/graphicsitem.h"
#include "mainwindow.h"

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

void MouseAction::shapePress(QMouseEvent *e)
{
    auto scene = MouseBehaviour::scene();
    // If nothing is selected or the selection area doesn't contain the point:
    if (scene->selectedItems().isEmpty() || !scene->selectionArea().contains(MouseBehaviour::scenePos(e->pos())))
    { selectionRect()->show(); updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::pos()); }

    // Otherwise move the object.
    else {

    }
}

void MouseAction::shapeDoubleClick(QMouseEvent *)
{

}

void MouseAction::shapeMove(QMouseEvent *)
{
    // If something is selected
    // .. if mouse click within selection, prepare to move

    // Otherwise, prepare selection rect.
    if (!MouseBehaviour::isPressed()) {return;}
    updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::moved());
}

void MouseAction::shapeRelease(QMouseEvent *)
{
    updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::scenePos());

    auto view = MouseBehaviour::view();
    QPainterPath path; path.addRect(selectionRect()->rect()); view->select(path);
    auto items = MouseBehaviour::view()->selectedItems();

    if (items.isEmpty()) { view->deselect(); CurvesSelected = {}; selectionRect()->hide(); }
    else {
        foreach (auto item, items) {
            Curve *curve = dynamic_cast<Curve *>(item);
            if (curve) {CurvesSelected.insert(curve);}
        }
    }
    // If mouse was double clicked, switch action to mouseVector
}

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

void MouseAction::vectorPress(QMouseEvent *e)
{
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
    // Node selection: move node

    // Vector selection
    // - move selected vector heads by diff in position of mouse
    // - if double clicked: all vectors have same relative position from their tails.
}

void MouseAction::vectorRelease(QMouseEvent *e)
{
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

template<typename T>
void MouseAction::press(QMouseEvent *e, QSet<T> &selected)
{

}

template<typename T>
void MouseAction::move(QMouseEvent *e, QSet<T> &selected)
{

}

template<typename T>
void MouseAction::release(QMouseEvent *e, QSet<T> &selected)
{

}
