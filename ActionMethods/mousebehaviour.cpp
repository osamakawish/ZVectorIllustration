#include "mousebehaviour.h"

#include <QCursor>
#include <QMouseEvent>
#include "graphicsview.h"

bool MouseBehaviour::IsPressed = false;
bool MouseBehaviour::IsDoubleClicked = false;
bool MouseBehaviour::rightClicked = false;
QPointF MouseBehaviour::Pos = QCursor::pos();
QPointF MouseBehaviour::DPos = QPointF();
std::unique_ptr<GraphicsView> MouseBehaviour::view = std::unique_ptr<GraphicsView>();

void MouseBehaviour::setView(GraphicsView *v)
{
    std::unique_ptr<GraphicsView> temp(v);
    view.swap(temp);
}

void MouseBehaviour::press()
{ IsPressed = true; }

void MouseBehaviour::doubleClick()
{ IsDoubleClicked = true; }

void MouseBehaviour::moveTo(QPointF pos)
{ DPos = pos - Pos; Pos = pos; }

void MouseBehaviour::move(QPointF dPos)
{ DPos = dPos; Pos += DPos; }

void MouseBehaviour::release()
{ IsPressed = false; IsDoubleClicked = false; }

bool MouseBehaviour::isPressed()
{ return IsPressed; }

bool MouseBehaviour::isDoubleClicked()
{ return IsDoubleClicked; }

QPointF MouseBehaviour::pos()
{ return Pos; }

QPointF MouseBehaviour::lastClickedPos()
{ return Pos - DPos; }

QPointF MouseBehaviour::scenePos()
{ return view->mapToScene(view->mapFromGlobal(QCursor::pos())); }

QPointF MouseBehaviour::scenePos(QMouseEvent *e)
{ return view->mapToScene(view->mapFrom(view.get(),e->pos())); }

//inline QPointF mapMousePosition(QMouseEvent *e)
//{ return mapToScene(mapFrom(this,e->pos())); }
//inline QPointF mapMousePosition(QPoint pos)
//{ return mapToScene(mapFromGlobal(pos)); }
//inline QPointF mouseViewPosition()
//{ return mapMousePosition(QCursor::pos()); }
