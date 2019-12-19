#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr);
};

#endif // GRAPHICSVIEW_H
