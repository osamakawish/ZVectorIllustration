#include "graphicsview.h"

#include "ActionMethods/mousebehaviour.h"
#include "ActionMethods/mouseaction.h"
#include "ActionMethods/penaction.h"
#include "ActionMethods/textaction.h"
#include "ActionMethods/zoomaction.h"

#include <QMouseEvent>
#include <limits>
#include <QDebug>

#include "../../../../GraphicsItems/Curves/curve.h"
#include "../../../../GraphicsItems/Shapes/shape.h"

MouseEvent GraphicsView::PRESS = MouseAction::shapePress;
MouseEvent GraphicsView::DOUBLE_CLICK = MouseAction::shapeDoubleClick;
MouseEvent GraphicsView::MOVE = MouseAction::shapeMove;
MouseEvent GraphicsView::RELEASE = MouseAction::shapeRelease;

void GraphicsView::initialize()
{
    setViewportUpdateMode(ViewportUpdateMode::FullViewportUpdate);

    setSceneRect(QRectF(0,0,200,400)); setBackgroundBrush(Qt::Dense6Pattern);
    SHEET_RECT = new QGraphicsRectItem(scene()->addRect(sceneRect(),QPen(),QBrush(Qt::white)));
    SHEET_RECT->setZValue(-std::numeric_limits<qreal>::max());
    setMouseTracking(true);

//    test();
}

void GraphicsView::test()
{
    Ellipse *ellipse = new Ellipse(QRectF(20,20,100,200)); scene()->addItem(ellipse);
    scene()->addRect(20,20,100,200);

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

GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(new QGraphicsScene,parent),
    SHAPE_CURVE_SELECTION(this), NODE_VECTOR_SELECTION(this)
{ initialize(); }

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent) : QGraphicsView(scene,parent),
    SHAPE_CURVE_SELECTION(this), NODE_VECTOR_SELECTION(this)
{ initialize(); }

GraphicsView::~GraphicsView()
{ delete SHEET_RECT; }

void GraphicsView::mousePressEvent(QMouseEvent *e)
{ Mouse::press(); PRESS(e); }

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *e)
{ Mouse::doubleClick(); DOUBLE_CLICK(e); }

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{ Mouse::moveTo(e->globalPos()); MOVE(e); }

void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{ Mouse::release(); RELEASE(e); }

