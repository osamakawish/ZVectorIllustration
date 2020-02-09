#include "mousebehaviour.h"

#include <QCursor>
#include <QDebug>
#include <QMouseEvent>
#include "../Windows/MainWindow/MainWidgets/GraphicsView/graphicsview.h"

namespace {
    bool IsPressed=false; bool IsDoubleClicked=false;
    bool RightClicked=false;
    QPointF Click=QPointF(); QPointF DClick=QPointF();
    QPointF Move=QPointF(); QPointF DMove=QPointF();
    QPointF Release=QPointF(); QPointF DRelease=QPointF();
    GraphicsView *View=nullptr;
    QGraphicsScene *Scene=nullptr;
}

void Mouse::setView(GraphicsView *v)
{
    if (v == nullptr) return;

    View = v;
    Scene = v->scene();
    Move = scenePos();
}

GraphicsView *Mouse::view()
{ return View; }

QGraphicsScene *Mouse::scene()
{ return Scene; }

void Mouse::press()
{ IsPressed = true; DClick = scenePos() - Click; Click += DClick; }

void Mouse::doubleClick()
{ IsDoubleClicked = true; }

QPointF Mouse::moved()
{ return Move; }

void Mouse::rightClick()
{ RightClicked = true; press(); }

void Mouse::moveTo(QPoint pos)
{ DMove = scenePos(pos) - Move; Move = Move + DMove; }

void Mouse::moveBy(QPoint dPos)
{ DMove = dPos; Move += DMove; }

void Mouse::release()
{ IsPressed = false; IsDoubleClicked = false; RightClicked = false;
DRelease = scenePos() - Release; Release = Release + DRelease; }

bool Mouse::isPressed()
{ return IsPressed; }

bool Mouse::isDoubleClicked()
{ return IsDoubleClicked; }

QPointF Mouse::pos()
{ return Click; }

QPointF Mouse::lastClickedPos()
{ return Click - DClick; }

QPointF Mouse::previousReleasedPos()
{ return Release - DRelease; }

QPointF Mouse::scenePos()
{ return View->mapToScene(View->mapFromGlobal(QCursor::pos())); }

QPointF Mouse::scenePos(QPoint p)
{ return View->mapToScene(View->mapFromGlobal(p)); }

QPointF Mouse::scenePos(QMouseEvent *e)
{ return View->mapToScene(View->mapFrom(View,e->pos())); }

QPointF Mouse::releasePos()
{ return Release; }

QPointF Mouse::movedBy()
{ return DMove; }
