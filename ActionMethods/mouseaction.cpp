
#include <QMouseEvent>

#include "mouseaction.h"
#include "graphicsview.h"
#include "mousebehaviour.h"

QPainterPath MouseAction::SelectionPath = QPainterPath();

void MouseAction::shapePress(QMouseEvent *e)
{
    // If something is selected
    // .. if mouse is clicked outside selection, deselect.
    // .. if mouse click within selection, prepare to move

    // Otherwise, prepare selection rect.
    SelectionPath = QPainterPath(e->pos());
    MouseBehaviour::scene()->setSelectionArea(SelectionPath);
}

void MouseAction::shapeDoubleClick(QMouseEvent */*e*/)
{}

void MouseAction::shapeMove(QMouseEvent *e)
{
    if (!MouseBehaviour::isPressed()) {return;}
    // If something is selected
    // .. if mouse is clicked outside selection, update selection rect.
    // .. if mouse click within selection, prepare to move

    // Otherwise, prepare selection rect.
    SelectionPath = QPainterPath();
    SelectionPath.addRect(GraphicsView::rectangle(MouseBehaviour::pos(),e->pos()));
    MouseBehaviour::scene()->setSelectionArea(SelectionPath);
}

void MouseAction::shapeRelease(QMouseEvent *e)
{

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
