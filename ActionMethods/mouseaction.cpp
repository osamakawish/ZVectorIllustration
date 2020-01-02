
#include <QMouseEvent>
#include <QDebug>

#include "mouseaction.h"
#include "graphicsview.h"
#include "mousebehaviour.h"

QPainterPath MouseAction::SelectionPath = QPainterPath();

void MouseAction::updateSelectionPath(QPointF p1, QPointF p2)
{
    QRectF rect = GraphicsView::rectangle(p1,p2);
    auto view = MouseBehaviour::view();
    SelectionPath = QPainterPath(); SelectionPath.addRect(rect);
    view->SelectionRect->setRect(rect);
    MouseBehaviour::scene()->setSelectionArea(SelectionPath);
}

void MouseAction::shapePress(QMouseEvent *e)
{
    auto scene = MouseBehaviour::scene();
    // If nothing is selected or the selection area doesn't contain the point:
    if (scene->selectedItems().isEmpty() || !scene->selectionArea().contains(e->pos()))
    {
        updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::pos());
        MouseBehaviour::view()->SelectionRect->show();
    }

    // Otherwise move the object.
    else {

    }
}

void MouseAction::shapeDoubleClick(QMouseEvent */*e*/)
{}

void MouseAction::shapeMove(QMouseEvent *e)
{
    if (!MouseBehaviour::isPressed()) {return;}
    updateSelectionPath(MouseBehaviour::pos(),MouseBehaviour::moved());
    // If something is selected
    // .. if mouse is clicked outside selection, update selection rect.
    // .. if mouse click within selection, prepare to move

    // Otherwise, prepare selection rect.
}

void MouseAction::shapeRelease(QMouseEvent *e)
{
    updateSelectionPath(MouseBehaviour::pos(),e->pos());
    auto items = MouseBehaviour::scene()->selectedItems();
    auto view = MouseBehaviour::view(); auto scene = MouseBehaviour::scene();

    if (items.isEmpty()) {
        view->SelectionRect->hide();

        if (view->SelectionGroup.get())
        scene->destroyItemGroup(view->SelectionGroup.release());
    }
    else {
        view->SelectionGroup.reset(scene->createItemGroup(items));
        view->SelectionRect->setRect(view->SelectionGroup->boundingRect());
    }
}

void MouseAction::vectorPress(QMouseEvent *e)
{

}

void MouseAction::vectorDoubleClick(QMouseEvent *e)
{

}

void MouseAction::vectorMove(QMouseEvent *e)
{

}

void MouseAction::vectorRelease(QMouseEvent *e)
{

}
