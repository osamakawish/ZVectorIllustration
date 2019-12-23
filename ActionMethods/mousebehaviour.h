#ifndef MOUSEBEHAVIOUR_H
#define MOUSEBEHAVIOUR_H

#include <memory>

class QWidget;
class GraphicsView; class QPoint; class QPointF; class QMouseEvent;

//inline QPointF mapPositionToGlobal(QPointF pos)
//{ return mapToGlobal(mapFromScene(pos)); }

class MouseBehaviour
{
    static bool IsPressed; static bool IsDoubleClicked;
    static bool rightClicked;
    static QPointF Pos; static QPointF DPos;
    static std::unique_ptr<GraphicsView> view;

public:
    static void setView(GraphicsView *view);

    static void press(); static void doubleClick();
    static void moveTo(QPointF pos);
    static void move(QPointF dPos); static void release();

    static bool isPressed(); static bool isDoubleClicked();
    static QPointF pos(); static QPointF lastClickedPos();
    static QPointF scenePos(); static QPointF scenePos(QMouseEvent *e);
};

#endif // MOUSEBEHAVIOUR_H
