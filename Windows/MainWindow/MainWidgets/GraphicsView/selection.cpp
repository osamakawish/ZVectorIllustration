#include "selection.h"
#include "ActionMethods/mousebehaviour.h"
#include "GraphicsItems/Curves/node.h"
#include "GraphicsItems/Curves/curve.h"

QRectF SelectionShapeCurve::SCALE_BUTTON_RECT= QRectF(-6,-6,12,12);
QRectF SelectionShapeCurve::MOVE_BUTTON_RECT = QRectF(-6,-6,12,12);

SelectionNodeVector::SelectionNodeVector(QGraphicsView *view) : Selection<Node, Vector>(view)
{ PEN = QPen(Qt::transparent); BRUSH = QBrush(QColor(0,0,0,16)); }

SelectionNodeVector::~SelectionNodeVector() {}

void SelectionNodeVector::select(Node *nd)
{ nd->select(); nd->showVectors(); }

void SelectionNodeVector::select(Vector *vector)
{ vector->select(); }

void SelectionNodeVector::deselect()
{ auto it = S_ITEMS.begin(); while (it != S_ITEMS.end()) { (*it)->hide(); it++; } }

// Select all nodes and vectors.
void SelectionNodeVector::finalizePath() { PATH->hide(); }

SelectionShapeCurve::SelectionShapeCurve(QGraphicsView *view) : Selection<Shape, Curve>(view)
{
    typedef QGraphicsItem::GraphicsItemFlag GFlag;

    PEN = QPen(Qt::DashLine); BRUSH = QBrush(Qt::transparent);
    QPainterPath path; path.addEllipse(MOVE_BUTTON_RECT);
    MOVE_BUTTON = SCENE->addPath(path,QPen(Qt::transparent),QBrush(QColor(0,0,0,128)));
    MOVE_BUTTON->setZValue(std::numeric_limits<qreal>::max());
    MOVE_BUTTON->setFlags(GFlag::ItemIsSelectable | GFlag::ItemIsMovable);
    initializeScaleButtons();

    showButtons(false);
}

SelectionShapeCurve::~SelectionShapeCurve() {}

void SelectionShapeCurve::select(Shape *) {}

void SelectionShapeCurve::select(Curve *curve) { curve->showNodes(); }

void SelectionShapeCurve::showNodes()
{ auto it = T_ITEMS.begin(); while (it != T_ITEMS.end()) {(*it)->showNodes(); it++;} }

void SelectionShapeCurve::showButtons(bool visible)
{
    resetTransformButtons();
    MOVE_BUTTON->setVisible(visible); auto it = SCALE_BUTTONS.begin();
    while (it != SCALE_BUTTONS.end()) { it.key()->setVisible(visible); it++; }
}

bool SelectionShapeCurve::shouldTransform()
{return SELECTED_BUTTON != nullptr;}

SelectionShapeCurve::TransformButton *SelectionShapeCurve::getTransformButton(QPointF pt)
{
    auto items = SCENE->items(pt); auto it = items.begin();
    while (it != items.end()) {
        QGraphicsPathItem *item = dynamic_cast<QGraphicsPathItem *>(*it); it++;
        if (item) {if ((MOVE_BUTTON == item) || (SCALE_BUTTONS.contains(item))) {return item;}}
    }
    return nullptr;
}

// Note: this isn't working for whatever reason. Need to try finding the center of transformation origin.
// which appears to be (0,0). translate to (0,0), rescale, then translate back.
void SelectionShapeCurve::setTransformOrigin(QGraphicsPathItem *item)
{
    QPointF pt = item->pos(); QPointF sz(8,8);
    TRANSFORMATION_ORIGIN = item->pos();
    SCENE->addRect(QRectF(pt-sz,pt+sz));
}

QPointF multiply(QPointF pt1, QPointF pt2)
{ return QPointF(pt1.x()*pt2.x(),pt1.y()*pt2.y()); }

void SelectionShapeCurve::resetTransformButtons()
{
    QRectF rect = selectionBoundingRect();
    QPointF center = rect.center();
    MOVE_BUTTON->setPos(center);
    QPointF df(rect.width() / 2,rect.height() / 2);

    auto it = SCALE_BUTTONS.begin();
    while (it != SCALE_BUTTONS.end())
    { QPointF pos = center + multiply(it.value(),df); it.key()->setPos(pos); it++; }
}

void SelectionShapeCurve::initializeScaleButtons()
{
    typedef QGraphicsItem::GraphicsItemFlag GFlag;

    // Setting the ellipse path
    QPainterPath path; path.addEllipse(SCALE_BUTTON_RECT);

    // Pair points from (-1,-1) to (1,1) not including (0,0)
    QList<QPointF> pairs;
    for (int i=-1; i<=1; i++) { for (int j=-1; j<=1; j++) { pairs.append(QPointF(i,j)); } }
    pairs.removeAll(QPointF(0,0));

    // Defining scale buttons
    auto it = pairs.begin(); while (it != pairs.end())
    {
        TransformButton *button = SCENE->addPath(path,QPen(),QColor(0,0,255,128));
        button->setFlags(GFlag::ItemIsSelectable | GFlag::ItemIsMovable);
        SCALE_BUTTONS.insert(button,*it); button->setZValue(std::numeric_limits<qreal>::max()); it++;
    }
}

void SelectionShapeCurve::applyTransformation()
{
    GROUP->setTransform(TRANSFORM_APPLIED);
    setPathRect(selectionBoundingRect());
    resetTransformButtons();
}

QPointF SelectionShapeCurve::rectBoundaryPoint(QPointF r, QRectF rect)
{
    QPointF o = rect.center(); qreal w = rect.width() / 2; qreal h = rect.height() / 2;
    return QPointF(o.x() + r.x()*w, o.y() + r.y()*h);
}


QRectF SelectionShapeCurve::selectionBoundingRect()
{ return GROUP->mapRectToScene(GROUP->boundingRect()); }

SelectionShapeCurve::TransformButton *SelectionShapeCurve::getAcrossScaleButton(SelectionShapeCurve::TransformButton *button)
{ QPointF pt = -SCALE_BUTTONS[button]; return SCALE_BUTTONS.key(pt); }

void SelectionShapeCurve::resizeToRect(QRectF newRect)
{
    QRectF oldRect = GROUP->boundingRect();

    QTransform transform;
    QPointF r = SCALE_BUTTONS[SELECTED_BUTTON];
    QPointF tl1 = rectBoundaryPoint(r,oldRect);
    transform.translate(-tl1.x(), -tl1.y());

    qreal sx = newRect.width() / oldRect.width();
    qreal sy = newRect.height() / oldRect.height();
    transform.scale(sx,sy);

    QPointF tl2 = rectBoundaryPoint(r,newRect);
    transform.translate(tl2.x(), tl2.y());

    TRANSFORM_APPLIED = transform;
}

// Corner reset
QPointF cr(QTransform &tr, QPointF pt) {return pt - tr.map(pt);}

void SelectionShapeCurve::scaleTransform(QPointF df)
{
    QSizeF sz = QRectF(TRANSFORMATION_ORIGIN,SELECTED_BUTTON->pos()).size();
    QPointF s = scaleFactors(df,sz);

    qreal x = TRANSFORMATION_ORIGIN.x(); qreal y = TRANSFORMATION_ORIGIN.y();
    qreal w = sz.width(); qreal h = sz.height();
    qreal a = s.x(); qreal b = s.y();

    TRANSFORM_APPLIED.scale(a,b);
    QPointF tr = cr(TRANSFORM_APPLIED,TRANSFORMATION_ORIGIN);
    TRANSFORM_APPLIED.translate(tr.x(),tr.y());
//    tr = cr(TRANSFORM_APPLIED,TRANSFORMATION_ORIGIN);
//    TRANSFORM_APPLIED.translate(tr.x(),tr.y());
    qDebug() << TRANSFORMATION_ORIGIN << TRANSFORM_APPLIED.map(TRANSFORMATION_ORIGIN);
}

bool SelectionShapeCurve::setTransform(QPointF pt)
{
    QGraphicsPathItem *item = getTransformButton(pt);
    if (SCALE_BUTTONS.contains(item))
    {
        SELECTED_BUTTON = item; TRANSFORM_BY = &SelectionShapeCurve::rescaleBy;
        setTransformOrigin(getAcrossScaleButton(item));
        return true;
    }
    else if (item == MOVE_BUTTON)
    { SELECTED_BUTTON = item; TRANSFORM_BY = &SelectionShapeCurve::moveBy; return true; }

    SELECTED_BUTTON = nullptr; return false;
}

void SelectionShapeCurve::transform(QPointF df, QPointF pt) {(this->*TRANSFORM_BY)(df,pt);}

void SelectionShapeCurve::deselect()
{ showButtons(false); }

QPointF SelectionShapeCurve::scaleFactors(QPointF df, QSizeF size)
{
    QPointF c = SCALE_BUTTONS[SELECTED_BUTTON];
    return QPointF((size.width()+df.x())/size.width(), (size.height()+df.y())/size.height());
}

qreal fix(qreal a, qreal b) { return -(a-1)*b/(2*a); }

void SelectionShapeCurve::rescaleBy(QPointF df, QPointF pt)
{
//    resizeToRect(QRectF(TRANSFORMATION_ORIGIN,pt));

    scaleTransform(df); // -> Works better : need to fix directions based on selected point and rate of rescale

    applyTransformation();
}

void move(QGraphicsItem *item, QPointF pt) {item->moveBy(pt.x(),pt.y());}

void SelectionShapeCurve::moveBy(QPointF df, QPointF pt)
{
    Selection<Shape, Curve>::moveBy(df, pt); move(MOVE_BUTTON,df);
    auto it = SCALE_BUTTONS.begin();
    while (it!=SCALE_BUTTONS.end()) { it.key()->moveBy(df.x(),df.y()); it++; }
}

void SelectionShapeCurve::finalizePath()
{ setPathRect(PATH->path().controlPointRect()); showButtons(true); }

QPointF SelectionShapeCurve::applyTransformToPoint(QTransform t, QPointF pt)
{
    qreal x = pt.x(); qreal y = pt.y();
    qreal sx = t.m11(); qreal sy = t.m22(); // scale x and y
    qreal Sx = t.m21(); qreal Sy = t.m12(); // shear x and y
    qreal dx = t.m31(); qreal dy = t.m32(); // translate x and y

    qreal x_ = sx*x + Sx*y + dx;
    qreal y_ = sy*y + Sy*x + dy;

    qreal px = t.m13();
    qreal py = t.m23();
    qreal pz = t.m33();
    if (!t.isAffine()) {
        qreal w_ = px*x + py*y + pz;
        x_ /= w_;
        y_ /= w_;
    }
    return QPointF(x_,y_);
}
