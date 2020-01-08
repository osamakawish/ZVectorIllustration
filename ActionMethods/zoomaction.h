#ifndef ZOOMACTION_H
#define ZOOMACTION_H

#include <QGraphicsItem>

class QMouseEvent;

class ZoomAction
{
    static const qreal DefaultClickZoomRatio;
    static const qreal DefaultDoubleClickZoomRatio;
    static QGraphicsRectItem *selectionRect;

public:
    static qreal ClickZoomRatio; static qreal DoubleClickZoomRatio;
    void restoreZoomRatiosToDefaults();

    static void shapePress(QMouseEvent *e);
    static void shapeDoubleClick(QMouseEvent *e);
    static void shapeMove(QMouseEvent *e);
    static void shapeRelease(QMouseEvent *e);
    static void shapeToggle(bool toggle);

    static void resetCurve();
    static void vectorPress(QMouseEvent *e);
    static void vectorDoubleClick(QMouseEvent *e);
    static void vectorMove(QMouseEvent *e);
    static void vectorRelease(QMouseEvent *e);
    static void vectorToggle(bool toggle);
};

#endif // ZOOMACTION_H
