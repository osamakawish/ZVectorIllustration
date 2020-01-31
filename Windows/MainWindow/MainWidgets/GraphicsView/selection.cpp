#include "selection.h"
#include "GraphicsItems/Curves/node.h"
#include "GraphicsItems/Curves/curve.h"

SelectionNodeVector::SelectionNodeVector(QGraphicsView *view) : Selection<Node, Vector>(view)
{ setRectPen(Qt::transparent); setRectBrush(QColor(0,0,0,32)); }

SelectionNodeVector::~SelectionNodeVector() {}

void SelectionNodeVector::selectS(Node *nd)
{ nd->select(); nd->showVectors(); }

void SelectionNodeVector::selectT(Vector *vector)
{ vector->select(); }

void SelectionNodeVector::finalizePath() { PATH->hide(); }

SelectionShapeCurve::SelectionShapeCurve(QGraphicsView *view) : Selection<Shape, Curve>(view)
{ setRectPen(Qt::DashLine); setRectBrush(Qt::transparent); }

SelectionShapeCurve::~SelectionShapeCurve() {}

void SelectionShapeCurve::selectS(Shape *) {}

void SelectionShapeCurve::selectT(Curve *curve) { curve->showNodes(); }

void SelectionShapeCurve::showNodes()
{ auto it = T_ITEMS.begin(); while (it != T_ITEMS.end()) {(*it)->showNodes(); it++;} }

void SelectionShapeCurve::finalizePath() { setPathRect(PATH->path().controlPointRect()); }
