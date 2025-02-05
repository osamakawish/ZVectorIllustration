#ifndef MOUSEBEHAVIOUR_H
#define MOUSEBEHAVIOUR_H

#include <memory>

// Should change these to namespaces eventually.

class QWidget; class QGraphicsScene;
class GraphicsView; class QPoint; class QPointF; class QMouseEvent;

#include <QPointF>

namespace Mouse
{
    void setView(GraphicsView *view);
    GraphicsView *view(); QGraphicsScene *scene();

    void press(); void doubleClick(); QPointF moved();
    void rightClick(); void moveTo(QPoint pos);
    void moveBy(QPoint dPos); void release();

    bool isPressed(); bool isDoubleClicked();
    QPointF pos(); QPointF movedBy(); QPointF releasePos();
    QPointF lastClickedPos(); QPointF previousReleasedPos();
    QPointF scenePos(); QPointF scenePos(QPoint p);
    QPointF scenePos(QMouseEvent *e);

    void setClickEvent();
};

#endif // MOUSEBEHAVIOUR_H
