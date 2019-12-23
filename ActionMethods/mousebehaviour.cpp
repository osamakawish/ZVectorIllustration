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
std::unique_ptr<GraphicsView> MouseBehaviour::View = std::unique_ptr<GraphicsView>();
std::unique_ptr<QGraphicsScene> MouseBehaviour::Scene = std::unique_ptr<QGraphicsScene>();

void MouseBehaviour::setView(GraphicsView *v)
{
//    qDebug() << v;
    if (v == nullptr) return;

    std::unique_ptr<GraphicsView> temp(v); View.swap(temp);
    std::unique_ptr<QGraphicsScene> temp2(v->scene()); Scene.swap(temp2);
    Move = scenePos();
}

GraphicsView *MouseBehaviour::view()
{ return View.get(); }

QGraphicsScene *MouseBehaviour::scene()
{ return Scene.get(); }

void MouseBehaviour::press()
{ IsPressed = true; DClick = scenePos() - Click; Click = scenePos(); }

void MouseBehaviour::doubleClick()
{ IsDoubleClicked = true; DClick = scenePos() - Click; Click = scenePos(); }

void MouseBehaviour::rightClick()
{ RightClicked = true; DClick = scenePos() - Click; Click = scenePos(); }

void MouseBehaviour::moveTo(QPointF pos)
{ DClick = pos - Click; Click = pos; }

void MouseBehaviour::move(QPointF dPos)
{ DClick = dPos; Click += DClick; }

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

QPointF MouseBehaviour::scenePos(QMouseEvent *e)
{ return View->mapToScene(View->mapFrom(View.get(),e->pos())); }

//inline QPointF mapMousePosition(QMouseEvent *e)
//{ return mapToScene(mapFrom(this,e->pos())); }
//inline QPointF mapMousePosition(QPoint pos)
//{ return mapToScene(mapFromGlobal(pos)); }
//inline QPointF mouseViewPosition()
//{ return mapMousePosition(QCursor::pos()); }
