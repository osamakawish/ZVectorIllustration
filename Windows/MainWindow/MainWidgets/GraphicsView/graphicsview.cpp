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
    SELECTION_RECT = new QGraphicsRectItem(scene()->addRect(QRectF()));
    SELECTION_RECT->setZValue(std::numeric_limits<qreal>::max());
    SELECTION_RECT->setPen(QPen(Qt::DashLine));
    SELECTION_GROUP = scene()->createItemGroup(QList<QGraphicsItem *>());
    setMouseTracking(true);

    test();
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

qreal GraphicsView::minZValue(QList<QGraphicsItem *> items)
{
    qreal min = std::numeric_limits<double>::max();
    foreach (auto item, items) {
        qreal n = item->zValue();
        if (n < min) min = n;
    }
    return min;
}

qreal GraphicsView::maxZValue(QList<QGraphicsItem *> items)
{
    qreal max = std::numeric_limits<double>::min();
    foreach (auto item, items) {
        qreal n = item->zValue();
        if (n > max) max = n;
    }
    return max;
}

void GraphicsView::selectAll(QList<QGraphicsItem *> items)
{ foreach (auto item, items) { dynamic_cast<Selectable *>(item)->select(); } }

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(new QGraphicsScene,parent), SHAPE_CURVE_SELECTION(this)
{ initialize(); }

GraphicsView::GraphicsView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene,parent), SHAPE_CURVE_SELECTION(this)
{ initialize(); }

GraphicsView::~GraphicsView()
{
    delete SELECTION_RECT;
    delete SHEET_RECT;
    scene()->destroyItemGroup(SELECTION_GROUP);
}

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
{ MouseBehaviour::press(); PRESS(e); }

void GraphicsView::mouseDoubleClickEvent(QMouseEvent *e)
{ MouseBehaviour::doubleClick(); DOUBLE_CLICK(e); }

void GraphicsView::mouseMoveEvent(QMouseEvent *e)
{ MouseBehaviour::moveTo(e->globalPos()); MOVE(e); }

void GraphicsView::mouseReleaseEvent(QMouseEvent *e)
{ MouseBehaviour::release(); RELEASE(e); }

QGraphicsRectItem *GraphicsView::selectionRect()
{ return SELECTION_RECT; }

QList<QGraphicsItem *> GraphicsView::selectedItems()
{ return SELECTION_GROUP->childItems(); }

void GraphicsView::deselect()
{ scene()->destroyItemGroup(SELECTION_GROUP); SELECTION_GROUP = scene()->createItemGroup(QList<QGraphicsItem *>());
SELECTION_RECT->setRect(QRectF()); SELECTION_RECT->hide(); }
