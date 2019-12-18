#include "valuesetter.h"
#include "ui_valuesetter.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <string>
#include <QtMath>
#include <QDebug>

ValueSetter::ValueSetter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueSetter)
{
    ui->setupUi(this);
    setValue(0); setMinimum(0); setMaximum(1000*Dpi);
    connect(ui->slider,&QSlider::valueChanged,this,&ValueSetter::setValue,Qt::UniqueConnection);
    connect(ui->spinbox,static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            this,&ValueSetter::setDoubleValue, Qt::UniqueConnection);
}

ValueSetter::~ValueSetter()
{
    delete ui;
}

void ValueSetter::setValue(int value)
{
    ui->slider->blockSignals(true); ui->spinbox->blockSignals(true);
    ui->spinbox->setValue(static_cast<double>(value)/Dpi); ui->slider->setValue(value);
    ui->slider->blockSignals(false); ui->spinbox->blockSignals(false);

    emit valueChanged(value);
}

void ValueSetter::setDoubleValue(double value)
{
    ui->slider->blockSignals(true); ui->spinbox->blockSignals(true);
    ui->spinbox->setValue(value); ui->slider->setValue(static_cast<int>(value*Dpi));
    ui->slider->blockSignals(false); ui->spinbox->blockSignals(false);

    emit valueChangedDouble(value);
}

void ValueSetter::setMinimum(int min)
{
    this->min = min;
    ui->spinbox->setMinimum(static_cast<double>(min)/Dpi); ui->slider->setMinimum(min);
    emit minimumChanged(min);
}

void ValueSetter::setMaximum(int max)
{
    this->max = max;
    ui->spinbox->setMaximum(static_cast<double>(max)/Dpi); ui->slider->setMaximum(max); emit maximumChanged(max);
}

double ValueSetter::round2(double val)
{
    double value = static_cast<int>(100*val+0.5);
    return static_cast<double>(value/100);
}
