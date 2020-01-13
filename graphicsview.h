#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <memory>

#include <QGraphicsItem>
#include <QGraphicsView>

class MouseAction;
class PenAction;
class TextAction;
class ZoomAction;

class MainWindow;

typedef void (*MouseEvent)(QMouseEvent *);

class GraphicsView : public QGraphicsView
{
    static MouseEvent Press, DoubleClick, Move, Release;
    QGraphicsRectItem *SelectionRect; QGraphicsItemGroup *SelectionGroup;
    QGraphicsRectItem *SheetRect;

    void initialize();
    void test();

    void filter(QGraphicsItem *item, QList<QGraphicsItem *> &items);
    void filter(QGraphicsItem::GraphicsItemFlag flag, QList<QGraphicsItem *> &items);
    template<class T>
    void filter(QList<QGraphicsItem *> &items);

    qreal minZValue(QList<QGraphicsItem *> items);
    qreal maxZValue(QList<QGraphicsItem *> items);

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
    void select(QRectF selectionRect);
    void select(QPainterPath selectionPath);
    QList<QGraphicsItem *> selectedItems();
    void deselect();

    friend class MouseAction; friend class PenAction;
    friend class TextAction; friend class ZoomAction;
    friend class MainWindow;
};

#endif // GRAPHICSVIEW_H
