#ifndef COLORSETTER_H
#define COLORSETTER_H

#include <QWidget>
#include <QColor>
#include <vector>

namespace Ui {
class ColorSetter;
}

class ColorSetter : public QWidget
{
    Q_OBJECT

    typedef void (QColor::*colorAxisSetter)(int,int,int,int);

public:
    explicit ColorSetter(QWidget *parent = nullptr);
    ~ColorSetter();

    int a() const; int x() const; int y() const; int z() const; int k() const;
    QColor::Spec specs() const; void setSpec(QColor::Spec const specs);

signals:
    void colorChanged(QColor clr);

private:
    void makeConnections();

    void setA(const int a);
    void setX(const int x); void setY(const int y); void setZ(const int z);
    void setK(const int k);
    void setRgbTootip(); void setCmykTootip(); void setHslTootip(); void setHsvTootip();
    void updateColor(); void setMaxX(int max);
    void hideK(); void showK();
    int A=255, X=0, Y=0, Z=0, K=0;
    colorAxisSetter colorSetter = &QColor::setRgb;
    QColor clr = QColor(0,0,0);
    Ui::ColorSetter *ui;
};

#endif // COLORSETTER_H
