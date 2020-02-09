#include "selection.h"
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

void SelectionShapeCurve::setTransformOrigin(QGraphicsPathItem *item)
{
    QPointF pt = item->pos(); SELECTED_BUTTON=item;
    PATH->setTransformOriginPoint(pt); GROUP->setTransformOriginPoint(pt);
}

QPointF multiply(QPointF pt1, QPointF pt2)
{ return QPointF(pt1.x()*pt2.x(),pt1.y()*pt2.y()); }

void SelectionShapeCurve::resetTransformButtons()
{
    QRectF rect = GROUP->boundingRect();
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

bool SelectionShapeCurve::setTransform(QPointF pt)
{
    QGraphicsPathItem *item = getTransformButton(pt);
    if (SCALE_BUTTONS.contains(item))
    { SELECTED_BUTTON = item; TRANSFORM_BY = &SelectionShapeCurve::rescaleBy; return true; }
    else if (item == MOVE_BUTTON)
    { SELECTED_BUTTON = item; TRANSFORM_BY = &SelectionShapeCurve::moveBy; return true; }

    SELECTED_BUTTON = nullptr; return false;
}

void SelectionShapeCurve::transform(QPointF pt) {(this->*TRANSFORM_BY)(pt);}

void SelectionShapeCurve::deselect()
{ showButtons(false); }

QPointF scaleFactors(QPointF df, QSizeF size)
{ return QPointF((size.width()+df.rx())/size.width(), (size.height()+df.ry())/size.height()); }

// Bug: Problem clearly has to do with transformation origin
void SelectionShapeCurve::rescaleBy(QPointF df)
{
    MOVE_BUTTON->setPos(MOVE_BUTTON->pos()+df);

    QPointF scale = scaleFactors(df,PATH->boundingRect().size());

    QTransform transform; transform.scale(scale.x(),scale.y());

    GROUP->setTransform(transform,true); setPathRect(GROUP->mapRectToScene(GROUP->boundingRect()));
    resetTransformButtons();
}

void move(QGraphicsItem *item, QPointF pt) {item->moveBy(pt.x(),pt.y());}

void SelectionShapeCurve::moveBy(QPointF df)
{
    Selection<Shape, Curve>::moveBy(df); move(MOVE_BUTTON,df);
    auto it = SCALE_BUTTONS.begin();
    while (it!=SCALE_BUTTONS.end()) { it.key()->moveBy(df.x(),df.y()); it++; }
}

void SelectionShapeCurve::finalizePath()
{ setPathRect(PATH->path().controlPointRect()); showButtons(true); }
