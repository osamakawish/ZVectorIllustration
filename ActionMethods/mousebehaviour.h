#ifndef MOUSEBEHAVIOUR_H
#define MOUSEBEHAVIOUR_H

#include <memory>

class QWidget; class QGraphicsScene;
class GraphicsView; class QPoint; class QPointF; class QMouseEvent;

//inline QPointF mapPositionToGlobal(QPointF pos)
//{ return mapToGlobal(mapFromScene(pos)); }

class MouseBehaviour
{
private:
    static bool IsPressed; static bool IsDoubleClicked;
    static bool RightClicked;
    static QPointF Click; static QPointF DClick;
    static QPointF Move; static QPointF DMove;
    static QPointF Release;
    static GraphicsView *View;
    static QGraphicsScene *Scene;

public:
    static void setView(GraphicsView *view);
    static GraphicsView *view(); static QGraphicsScene *scene();

    static void press(); static void doubleClick(); static QPointF moved();
    static void rightClick(); static void moveTo(QPoint pos);
    static void move(QPoint dPos); static void release();

    static bool isPressed(); static bool isDoubleClicked();
    static QPointF pos(); static QPointF lastClickedPos();
    static QPointF scenePos(); static QPointF scenePos(QPoint p);
    static QPointF scenePos(QMouseEvent *e);
};

#endif // MOUSEBEHAVIOUR_H
