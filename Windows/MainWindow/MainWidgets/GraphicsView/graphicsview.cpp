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

    test();
}

void GraphicsView::test()
{
    auto rct = QRectF(30,30,100,200);
    auto rct1 = QRectF(80,50,90,150);
    Ellipse *ell = new Ellipse(rct); scene()->addItem(ell);
    ell->setZValue(20);

    QTransform t;
    qreal cx = rct1.width() / rct.width();
    qreal cy = rct1.height() / rct.height();
    QPointF d = rct1.topLeft() - rct.topLeft();

    t.scale(cx,cy);
//    qDebug() << t.map(rct) << QPolygonF(rct1) << cx << cy;

    ell->setTransform(t);


//    ell->setTransform(QTransform())

//    Ellipse *e1 = new Ellipse(QRectF(20,20,100,200)); addItem(e1);
//    qreal a = 1.5; qreal b = 2;
//    e1->setTransform(QTransform().scale(a,b).translate(-(a-1)*100/(a*2),-(b-1)*200/(b*2)));

//    QGraphicsRectItem *e2 = new QGraphicsRectItem(rct); addItem(e2);
//    qreal c = 0; qreal d = 1; qreal x = rct.center().x(); qreal y = rct.center().y();
//    QTransform shr = QTransform().shear(c,d).translate(-c*y,-d*x); -> Returns object to its center
//    e2->setTransform(shr);
//    qDebug() << shr.map(rct) << shr.map(rct.center());

    auto rect = scene()->addRect(rct); rect->setPen(QPen(Qt::red));
    auto rect1 = scene()->addRect(rct1); rect1->setPen(QPen(Qt::yellow));

    QPointF df(8,8);
    QPointF pt = ell->transformOriginPoint();
//    QPointF pt1 = e1->transformOriginPoint();
    scene()->addRect(QRectF(pt-df,pt+df));
//    scene()->addRect(QRectF(pt1-df,pt1+df));
}

void GraphicsView::test2()
{
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

void GraphicsView::addItem(QGraphicsItem *item)
{ scene()->addItem(item); item->setZValue(Z_VALUE); Z_VALUE++; }

void GraphicsView::debug()
{
    auto it = items().begin();
    while (it != items().end())
    { qDebug() << *it << (*it)->zValue() << endl; }
}

