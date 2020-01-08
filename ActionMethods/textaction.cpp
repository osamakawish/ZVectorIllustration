#include "textaction.h"

#include "../graphicsview.h"

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
        GraphicsView::Press = &TextAction::shapePress;
        GraphicsView::DoubleClick = &TextAction::shapeDoubleClick;
        GraphicsView::Move = &TextAction::shapeMove;
        GraphicsView::Release = &TextAction::shapeRelease;
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
        GraphicsView::Press = &TextAction::vectorPress;
        GraphicsView::DoubleClick = &TextAction::vectorDoubleClick;
        GraphicsView::Move = &TextAction::vectorMove;
        GraphicsView::Release = &TextAction::vectorRelease;
    }
    else {}
}
