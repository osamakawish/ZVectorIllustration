#include "graphicsview.h"

#include "ActionMethods/mousebehaviour.h"
#include "ActionMethods/mouseaction.h"
#include "ActionMethods/penaction.h"
#include "ActionMethods/textaction.h"
#include "ActionMethods/zoomaction.h"

#include <QMouseEvent>
#include <limits>
#include <QDebug>

#include "Curves/curve.h"

MouseEvent GraphicsView::Press = MouseAction::shapePress;
MouseEvent GraphicsView::DoubleClick = MouseAction::shapeDoubleClick;
MouseEvent GraphicsView::Move = MouseAction::shapeMove;
MouseEvent GraphicsView::Release = MouseAction::shapeRelease;

void GraphicsView::initialize()
{
    setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);

    SelectionRect = RectItemPtr(scene()->addRect(QRectF()));
    setSceneRect(QRectF(0,0,200,400)); setBackgroundBrush(Qt::Dense6Pattern);
    SelectionRect->setZValue(std::numeric_limits<double>::max());
    SheetRect = RectItemPtr(scene()->addRect(sceneRect(),QPen(),QBrush(Qt::white)));
    SheetRect->setZValue(-std::numeric_limits<double>::max());
    setMouseTracking(true);

    test();
}

void GraphicsView::test()
{
    QGraphicsEllipseItem *ellipse = scene()->addEllipse(0,0,100,200);
    QGraphicsLineItem *line = scene()->addLine(20,20,300,100);
    line->setParentItem(ellipse);

    ellipse->setFlag(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable);
    ellipse->setZValue(20);

    // Vector Test
    Vector *v = new Vector(QPointF(30,100),QPointF(-50,80)); scene()->addItem(v);
    scene()->addEllipse((30)-6,(100)-6,12,12); scene()->addEllipse((-50)-6,(80)-6,12,12);
    Vector *w = new Vector(QPointF(30,100),QPointF(-50,80)); scene()->addItem(w);
    w->tail(QPointF(80,100));
    Vector *u = new Vector(QPointF(30,100),QPointF(-50,80)); scene()->addItem(u);
    u->setPos(QPointF(120,190));

    // Curve and Node Test
    Curve *c = new Curve(QPointF(),scene());
    Node *nd = c->add(QPointF(200,50)); nd->outVector()->scene();
    nd->outVector(QPointF(20,50));
    c->add(QPointF(100,80));
    c->showNodes(); c->showVectors();
}

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent)
{ setScene(new QGraphicsScene); initialize(); }

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent)
{ initialize(); }

QRectF GraphicsView::rectangle(const QPointF &p1, const QPointF &p2)
{
    double minX, maxX, minY, maxY;

    if (p1.x() < p2.x()) {minX = p1.x(); maxX = p2.x();}
    else {minX = p2.x(); maxX = p1.x();}

    if (p1.y() < p2.y()) {minY = p1.y(); maxY = p2.y();}
    else {minY = p2.y(); maxY = p1.y();}

    return QRectF(QPointF(minX,minY),QPointF(maxX,maxY));
}

void GraphicsView::mousePressEvent(QMouseEvent *e)
{ MouseBehaviour::press(); Press(e); }

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *e)
{ MouseBehaviour::doubleClick(); DoubleClick(e); }

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{ MouseBehaviour::moveTo(e->globalPos()); Move(e); }

void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{ MouseBehaviour::release(); Release(e); }
