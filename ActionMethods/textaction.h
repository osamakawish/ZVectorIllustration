#ifndef TEXTACTION_H
#define TEXTACTION_H

class QMouseEvent;

class TextAction
{
public:
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

#endif // TEXTACTION_H
