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
    QGraphicsRectItem *SELECTION_RECT; QGraphicsItemGroup *SELECTION_GROUP;
    QGraphicsRectItem *SHEET_RECT;

    SelectionShapeCurve SHAPE_CURVE_SELECTION;

    void initialize();
    void test();

    static void filterOut(QGraphicsItem *item, QList<QGraphicsItem *> &items) { items.removeAll(item); }

    static void filterIn(QGraphicsItem::GraphicsItemFlag flag, QList<QGraphicsItem *> &items)
    { int i=0; while (i<items.length()) { if (items[i]->flags().testFlag(flag)) {i++;} else {items.removeAt(i);} } }

    template<class T>
    static void filterIn(QList<QGraphicsItem *> &items)
    { int i=0; while (i<items.length()) { if (dynamic_cast<T *>(items[i])) {i++;} else {items.removeAt(i);} } }

    template<class T>
    static void filterOut(QList<QGraphicsItem *> &items)
    { int i=0; while (i<items.length()) { if (dynamic_cast<T *>(items[i])) {items.removeAt(i);} else {i++;} } }

    qreal minZValue(QList<QGraphicsItem *> items);
    qreal maxZValue(QList<QGraphicsItem *> items);

    void selectAll(QList<QGraphicsItem *>);

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

    template <typename T>
    void select(QRectF selectionRect)
    { QPainterPath path = QPainterPath(); path.addRect(selectionRect); select<T>(path); }

    template <typename T>
    void select(QPainterPath selectionPath)
    {
        QList<QGraphicsItem *> items = scene()->items(selectionPath);

        // Ensures all items are selectable items of type T.
        filterIn<T>(items); filterIn(QGraphicsItem::GraphicsItemFlag::ItemIsSelectable, items);

        if (std::is_base_of<Selectable,T>::value) { selectAll(items); } // Need to counter this with a deselectAll()
        else {
        SELECTION_GROUP = scene()->createItemGroup(items); SELECTION_GROUP->setZValue(maxZValue(items));
        SELECTION_RECT->setRect(SELECTION_GROUP->boundingRect()); SELECTION_RECT->setZValue(std::numeric_limits<qreal>::max());
        SELECTION_RECT->show();
        }
    }

    QList<QGraphicsItem *> selectedItems();
    void deselect(); // Need means to deselect nodes and vectors too.

    friend class MouseAction; friend class PenAction;
    friend class TextAction; friend class ZoomAction;
    friend class MainWindow;
};

#endif // GRAPHICSVIEW_H
