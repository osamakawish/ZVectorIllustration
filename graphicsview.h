#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class MouseAction;
class PenAction;
class TextAction;
class ZoomAction;

class GraphicsView : public QGraphicsView
{
    typedef void (*MouseEvent)(QMouseEvent *);

    MouseEvent press, doubleClick, move, release;

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
};

#endif // GRAPHICSVIEW_H
