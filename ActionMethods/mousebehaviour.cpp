#include "mousebehaviour.h"

#include <QCursor>
#include <QDebug>
#include <QMouseEvent>
#include "graphicsview.h"

bool MouseBehaviour::IsPressed = false;
bool MouseBehaviour::IsDoubleClicked = false;
bool MouseBehaviour::RightClicked = false;

QPointF MouseBehaviour::Click = QPointF();
QPointF MouseBehaviour::DClick = QPointF();
QPointF MouseBehaviour::Move = QPointF();
QPointF MouseBehaviour::DMove = QPointF();
QPointF MouseBehaviour::Release = QPointF();

GraphicsView *MouseBehaviour::View = nullptr;
QGraphicsScene *MouseBehaviour::Scene = nullptr;

void MouseBehaviour::setView(GraphicsView *v)
{
//    qDebug() << v;
    if (v == nullptr) return;

    View = v;
    Scene = v->scene();
    Move = scenePos();
}

GraphicsView *MouseBehaviour::view()
{ return View; }

QGraphicsScene *MouseBehaviour::scene()
{ return Scene; }

void MouseBehaviour::press()
{ IsPressed = true; DClick = scenePos() - Click; Click += DClick; }

void MouseBehaviour::doubleClick()
{ IsDoubleClicked = true; qDebug() << 11 << Click; }

QPointF MouseBehaviour::moved()
{ return Move; }

void MouseBehaviour::rightClick()
{ RightClicked = true; press(); }

void MouseBehaviour::moveTo(QPoint pos)
{ DMove = pos - Move; Move = scenePos(pos); }

void MouseBehaviour::move(QPoint dPos)
{ DMove = dPos; Move += DMove; qDebug() << Move; }

void MouseBehaviour::release()
{ IsPressed = false; IsDoubleClicked = false; RightClicked = false; Release = scenePos(); }

bool MouseBehaviour::isPressed()
{ return IsPressed; }

bool MouseBehaviour::isDoubleClicked()
{ return IsDoubleClicked; }

QPointF MouseBehaviour::pos()
{ return Click; }

QPointF MouseBehaviour::lastClickedPos()
{ return Click - DClick; }

QPointF MouseBehaviour::scenePos()
{ return View->mapToScene(View->mapFromGlobal(QCursor::pos())); }

QPointF MouseBehaviour::scenePos(QPoint p)
{ return View->mapToScene(View->mapFromGlobal(p)); }

QPointF MouseBehaviour::scenePos(QMouseEvent *e)
{ return View->mapToScene(View->mapFrom(View,e->pos())); }

//inline QPointF mapMousePosition(QMouseEvent *e)
//{ return mapToScene(mapFrom(this,e->pos())); }
//inline QPointF mapMousePosition(QPoint pos)
//{ return mapToScene(mapFromGlobal(pos)); }
//inline QPointF mouseViewPosition()
//{ return mapMousePosition(QCursor::pos()); }
