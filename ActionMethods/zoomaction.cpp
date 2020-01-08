#include "zoomaction.h"

#include "../graphicsview.h"

const qreal ZoomAction::DefaultClickZoomRatio=1.2;
const qreal ZoomAction::DefaultDoubleClickZoomRatio=1.25;
qreal ZoomAction::ClickZoomRatio=1.2;
qreal ZoomAction::DoubleClickZoomRatio=1.25;

void ZoomAction::restoreZoomRatiosToDefaults()
{ ClickZoomRatio = DefaultClickZoomRatio; DoubleClickZoomRatio = DefaultDoubleClickZoomRatio; }

void ZoomAction::shapePress(QMouseEvent *e)
{

}

void ZoomAction::shapeDoubleClick(QMouseEvent *e)
{

}

void ZoomAction::shapeMove(QMouseEvent *e)
{

}

void ZoomAction::shapeRelease(QMouseEvent *e)
{

}

void ZoomAction::shapeToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::Press = &ZoomAction::shapePress;
        GraphicsView::DoubleClick = &ZoomAction::shapeDoubleClick;
        GraphicsView::Move = &ZoomAction::shapeMove;
        GraphicsView::Release = &ZoomAction::shapeRelease;
    }
    else {}
}

void ZoomAction::vectorPress(QMouseEvent *e)
{

}

void ZoomAction::vectorDoubleClick(QMouseEvent *e)
{

}

void ZoomAction::vectorMove(QMouseEvent *e)
{

}

void ZoomAction::vectorRelease(QMouseEvent *e)
{

}

void ZoomAction::vectorToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::Press = &ZoomAction::vectorPress;
        GraphicsView::DoubleClick = &ZoomAction::vectorDoubleClick;
        GraphicsView::Move = &ZoomAction::vectorMove;
        GraphicsView::Release = &ZoomAction::vectorRelease;
    }
    else {}
}
