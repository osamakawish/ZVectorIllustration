#include "graphicsview.h"
#include "ActionMethods/mousebehaviour.h"

#include <QMouseEvent>

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{
}

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent)
{

}

void GraphicsView::mousePressEvent(QMouseEvent *e)
{ MouseBehaviour::press(); press(e); }

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *e)
{ MouseBehaviour::doubleClick(); press(e); }

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{ MouseBehaviour::moveTo(e->pos()); move(e); }

void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{ MouseBehaviour::release(); release(e); }
