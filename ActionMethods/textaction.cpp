#include "textaction.h"

#include "../Windows/MainWindow/MainWidgets/GraphicsView/graphicsview.h"

void TextAction::shapePress(QMouseEvent *e)
{

}

void TextAction::shapeDoubleClick(QMouseEvent *e)
{

}

void TextAction::shapeMove(QMouseEvent *e)
{

}

void TextAction::shapeRelease(QMouseEvent *e)
{

}

void TextAction::shapeToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::PRESS = &TextAction::shapePress;
        GraphicsView::DOUBLE_CLICK = &TextAction::shapeDoubleClick;
        GraphicsView::MOVE = &TextAction::shapeMove;
        GraphicsView::RELEASE = &TextAction::shapeRelease;
    }
    else {}
}

void TextAction::vectorPress(QMouseEvent *e)
{

}

void TextAction::vectorDoubleClick(QMouseEvent *e)
{

}

void TextAction::vectorMove(QMouseEvent *e)
{

}

void TextAction::vectorRelease(QMouseEvent *e)
{

}

void TextAction::vectorToggle(bool toggle)
{
    if (toggle) {
        GraphicsView::PRESS = &TextAction::vectorPress;
        GraphicsView::DOUBLE_CLICK = &TextAction::vectorDoubleClick;
        GraphicsView::MOVE = &TextAction::vectorMove;
        GraphicsView::RELEASE = &TextAction::vectorRelease;
    }
    else {}
}
