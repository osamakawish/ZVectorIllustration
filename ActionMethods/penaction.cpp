#include "penaction.h"

#include "mousebehaviour.h"
#include "../GraphicsItems/Curves/curve.h"
#include "../Windows/MainWindow/MainWidgets/GraphicsView/graphicsview.h"

#include <QDebug>

Curve *PenAction::CurrentCurve = nullptr;
bool PenAction::OnFirstPoint = true;

void PenAction::updateCurrentNode()
{
    QPointF from = Mouse::pos(); QPointF to = Mouse::scenePos();
    Node *nd = CurrentCurve->selected();
    nd->inVector(2*from - to); nd->outVector(to);
    nd->showVectors();
}

void PenAction::shapePress(QMouseEvent *)
{
    CurrentCurve = new Curve(Mouse::pos(),Mouse::view()->scene());
}

void PenAction::shapeDoubleClick(QMouseEvent *)
{

}

void PenAction::shapeMove(QMouseEvent *)
{
    if (Mouse::isPressed())
    CurrentCurve->add(Mouse::moved());
}

void PenAction::shapeRelease(QMouseEvent *)
{
    resetCurve();
}

void PenAction::shapeToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::PRESS = &PenAction::shapePress;
        GraphicsView::DOUBLE_CLICK = &PenAction::shapeDoubleClick;
        GraphicsView::MOVE = &PenAction::shapeMove;
        GraphicsView::RELEASE = &PenAction::shapeRelease;
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
    {CurrentCurve = new Curve(Mouse::pos(),Mouse::view()->scene());}
    else
    {CurrentCurve->add(Mouse::pos());}
}

void PenAction::vectorDoubleClick(QMouseEvent *)
{

}

void PenAction::vectorMove(QMouseEvent *)
{
    if (Mouse::isPressed()) {
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
        GraphicsView::PRESS = &PenAction::vectorPress;
        GraphicsView::DOUBLE_CLICK = &PenAction::vectorDoubleClick;
        GraphicsView::MOVE = &PenAction::vectorMove;
        GraphicsView::RELEASE = &PenAction::vectorRelease;
    }
    else {resetCurve();}
}

