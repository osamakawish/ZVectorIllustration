#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <memory>

#include <QGraphicsItem>
#include <QGraphicsView>

#include "GraphicsItems/graphicsitem.h"
#include "selection.h"

class MouseAction;
class PenAction;
class TextAction;
class ZoomAction;

class MainWindow;

typedef void (*MouseEvent)(QMouseEvent *);

class GraphicsView : public QGraphicsView
{
    static MouseEvent PRESS, DOUBLE_CLICK, MOVE, RELEASE;
    QGraphicsRectItem *SHEET_RECT;

    SelectionShapeCurve SHAPE_CURVE_SELECTION;
    SelectionNodeVector NODE_VECTOR_SELECTION;

    void initialize();
    void test();

public:
    GraphicsView(QWidget *parent = nullptr);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsView();

    static QRectF rectangle(const QPointF &p1, const QPointF &p2);

    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    QGraphicsRectItem *selectionRect();

    QList<QGraphicsItem *> selectedItems();
    void deselectNodesVectors();
    void deselectAll(); // Need means to deselect nodes and vectors too.

    friend class MouseAction; friend class PenAction;
    friend class TextAction; friend class ZoomAction;
    friend class MainWindow;
};

#endif // GRAPHICSVIEW_H
