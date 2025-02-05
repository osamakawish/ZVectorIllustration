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
    qreal Z_VALUE=1;

    static MouseEvent PRESS, DOUBLE_CLICK, MOVE, RELEASE;
    QGraphicsRectItem *SHEET_RECT;

    SelectionShapeCurve SHAPE_CURVE_SELECTION;
    SelectionNodeVector NODE_VECTOR_SELECTION;

    void initialize();
    void test(); void test2();

public:
    GraphicsView(QWidget *parent = nullptr);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
    ~GraphicsView();

    void mousePressEvent(QMouseEvent *e) override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
    void mouseReleaseEvent(QMouseEvent *e) override;

    void addItem(QGraphicsItem *item);
    void debug();

    friend class MouseAction; friend class PenAction;
    friend class TextAction; friend class ZoomAction;
    friend class MainWindow;

    friend class FileWidget;
};

#endif // GRAPHICSVIEW_H
