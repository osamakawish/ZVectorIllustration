#include "penaction.h"

#include "mousebehaviour.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../Windows/MainWindow/MainWidgets/graphicsview.h"

#include <QDebug>

Curve *PenAction::CurrentCurve = nullptr;
bool PenAction::OnFirstPoint = true;

void PenAction::updateCurrentNode()
{
    QPointF from = MouseBehaviour::pos(); QPointF to = MouseBehaviour::scenePos();
    Node *nd = CurrentCurve->selected();
    nd->inVector(2*from - to); nd->outVector(to);
    nd->showVectors();
}

void PenAction::shapePress(QMouseEvent *)
{
    CurrentCurve = new Curve(MouseBehaviour::pos(),MouseBehaviour::view()->scene());
}

void PenAction::shapeDoubleClick(QMouseEvent *)
{

}

void PenAction::shapeMove(QMouseEvent *)
{
    if (MouseBehaviour::isPressed())
    CurrentCurve->add(MouseBehaviour::moved());
}

void PenAction::shapeRelease(QMouseEvent *)
{
    resetCurve();
}

void PenAction::shapeToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::Press = &PenAction::shapePress;
        GraphicsView::DoubleClick = &PenAction::shapeDoubleClick;
        GraphicsView::Move = &PenAction::shapeMove;
        GraphicsView::Release = &PenAction::shapeRelease;
    }
    else {}
}

void PenAction::resetCurve()
{
    OnFirstPoint = true; CurrentCurve = nullptr;
}

void PenAction::vectorPress(QMouseEvent *)
{
    // Create a new curve
    if (OnFirstPoint)
    {CurrentCurve = new Curve(MouseBehaviour::pos(),MouseBehaviour::view()->scene());}
    else
    {CurrentCurve->add(MouseBehaviour::pos());}
}

void PenAction::vectorDoubleClick(QMouseEvent *)
{

}

void PenAction::vectorMove(QMouseEvent *)
{
    if (MouseBehaviour::isPressed()) {
        updateCurrentNode();
    }
}

void PenAction::vectorRelease(QMouseEvent *)
{
    if (OnFirstPoint) {OnFirstPoint=false;}

    CurrentCurve->selected()->hideVectors();
}

void PenAction::vectorToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::Press = &PenAction::vectorPress;
        GraphicsView::DoubleClick = &PenAction::vectorDoubleClick;
        GraphicsView::Move = &PenAction::vectorMove;
        GraphicsView::Release = &PenAction::vectorRelease;
    }
    else {resetCurve();}
}

