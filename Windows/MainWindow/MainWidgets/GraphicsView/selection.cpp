#include "selection.h"
#include "GraphicsItems/Curves/node.h"
#include "GraphicsItems/Curves/curve.h"

SelectionNodeVector::SelectionNodeVector(QGraphicsView *view) : Selection<Node, Vector>(view)
{ PEN = QPen(Qt::transparent); BRUSH = QBrush(QColor(0,0,0,16)); }

SelectionNodeVector::~SelectionNodeVector() {}

void SelectionNodeVector::select(Node *nd)
{ nd->select(); nd->showVectors(); }

void SelectionNodeVector::select(Vector *vector)
{ vector->select(); }

// Select all nodes and vectors.
void SelectionNodeVector::finalizePath() { PATH->hide(); }

SelectionShapeCurve::SelectionShapeCurve(QGraphicsView *view) : Selection<Shape, Curve>(view)
{ PEN = QPen(Qt::DashLine); BRUSH = QBrush(Qt::transparent); }

SelectionShapeCurve::~SelectionShapeCurve() {}

void SelectionShapeCurve::select(Shape *) {}

void SelectionShapeCurve::select(Curve *curve) { curve->showNodes(); }

void SelectionShapeCurve::showNodes()
{ auto it = T_ITEMS.begin(); while (it != T_ITEMS.end()) {(*it)->showNodes(); it++;} }

void SelectionShapeCurve::finalizePath() { setPathRect(PATH->path().controlPointRect()); }
