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
typedef std::unique_ptr<QGraphicsRectItem> RectItemPtr;
typedef std::unique_ptr<QGraphicsItemGroup> ItemGroupPtr;

class GraphicsView : public QGraphicsView
{
    static MouseEvent Press, DoubleClick, Move, Release;
    RectItemPtr SelectionRect; ItemGroupPtr SelectionGroup;
    RectItemPtr SheetRect;

public:
    GraphicsView(QWidget *parent = nullptr);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);

    static QRectF rectangle(const QPointF &p1, const QPointF &p2);

    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    friend class MouseAction; friend class PenAction;
    friend class TextAction; friend class ZoomAction;
    friend class MainWindow;
};

#endif // GRAPHICSVIEW_H
