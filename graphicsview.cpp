#include "graphicsview.h"


GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{

}

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent)
{

}
