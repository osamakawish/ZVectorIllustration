#ifndef VALUESETTER_H
#define VALUESETTER_H

#include <QSlider>
#include <QSpinBox>
#include <QWidget>
#include <memory>

namespace Ui {
class ValueSetter;
}

class ValueSetter : public QWidget
{
    Q_OBJECT

public:
    explicit ValueSetter(QWidget *parent = nullptr);
    ~ValueSetter();

    void dpi(int dpi);
    void setUnits(QString units);
    void setDecimals(int d);
    void setValue(int value);
    void setDoubleValue(double value);
    void setMinimum(int minimum);
    void setMaximum(int maximum);

signals:
    void valueChanged(int);
    void valueChangedDouble(double);
    void minimumChanged(int);
    void maximumChanged(int);

private:
    double round2(double val);
    int val, min, max;

    int Dpi=72;
    Ui::ValueSetter *ui;
};

#endif // VALUESETTER_H
