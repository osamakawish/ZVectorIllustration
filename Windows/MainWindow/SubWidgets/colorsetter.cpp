#include "colorsetter.h"
#include "ui_colorsetter.h"

#include <QDebug>

ColorSetter::ColorSetter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorSetter)
{
    ui->setupUi(this); hideK(); makeConnections(); setRgbTootip();
    ui->aLabel->setToolTip("Alpha/Transparency"); ui->kLabel->setToolTip("Key/Black");
}

void ColorSetter::makeConnections()
{
    connect(ui->aSlider,static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),this,&ColorSetter::setA);
    connect(ui->xSlider,static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),this,&ColorSetter::setX);
    connect(ui->ySlider,static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),this,&ColorSetter::setY);
    connect(ui->zSlider,static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),this,&ColorSetter::setZ);
    connect(ui->kSlider,static_cast<void (QSlider::*)(int)>(&QSlider::valueChanged),this,&ColorSetter::setK);

    connect(ui->aSpin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ColorSetter::setA);
    connect(ui->xSpin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ColorSetter::setX);
    connect(ui->ySpin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ColorSetter::setY);
    connect(ui->zSpin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ColorSetter::setZ);
    connect(ui->kSpin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),this,&ColorSetter::setK);
}

ColorSetter::~ColorSetter()
{
    delete ui;
}

int ColorSetter::a() const
{ return A; }

int ColorSetter::x() const { return X; }

int ColorSetter::y() const { return Y; }

int ColorSetter::z() const { return Z; }

void ColorSetter::setA(const int a)
{ ui->aSlider->setValue(a); ui->aSpin->setValue(a); A=a; updateColor(); }

void ColorSetter::setX(const int x)
{ ui->xSlider->setValue(x); ui->xSpin->setValue(x); X=x; updateColor(); }

void ColorSetter::setY(const int y)
{ ui->ySlider->setValue(y); ui->ySpin->setValue(y); Y=y; updateColor(); }

void ColorSetter::setZ(const int z)
{ ui->zSlider->setValue(z); ui->zSpin->setValue(z); Z=z; updateColor(); }

void ColorSetter::setK(const int k)
{ if (clr.spec() == QColor::Cmyk) { K = k; ui->kSlider->setValue(k); ui->kSpin->setValue(k); updateColor();} }

void ColorSetter::setRgbTootip()
{ ui->xLabel->setToolTip("Red"); ui->yLabel->setToolTip("Green"); ui->zLabel->setToolTip("Blue"); }

void ColorSetter::setCmykTootip()
{ ui->xLabel->setToolTip("Cyan"); ui->yLabel->setToolTip("Magenta"); ui->zLabel->setToolTip("Yellow"); }

void ColorSetter::setHslTootip()
{ ui->xLabel->setToolTip("Hue"); ui->yLabel->setToolTip("Saturation"); ui->zLabel->setToolTip("Lightness"); }

void ColorSetter::setHsvTootip()
{ ui->xLabel->setToolTip("Hue"); ui->yLabel->setToolTip("Saturation"); ui->zLabel->setToolTip("Value"); }

QColor::Spec ColorSetter::specs() const
{ return clr.spec(); }

void ColorSetter::setSpec(const QColor::Spec specs)
{
    if (specs == clr.spec() || specs == QColor::Invalid) {return;}

    clr = clr.convertTo(specs);

    if (specs == QColor::Cmyk)
    { X = clr.cyan(); Y = clr.magenta(); Z = clr.yellow(); K = clr.black(); showK(); setMaxX(255); setK(K);
    ui->xLabel->setText("C"); ui->yLabel->setText("M"); ui->zLabel->setText("Y"); setCmykTootip(); }
    else { setK(0); hideK(); }

    switch (specs)
    { case QColor::Rgb: colorSetter = &QColor::setRgb;
        X = clr.red(); Y = clr.green(); Z = clr.blue(); setMaxX(255); setRgbTootip();
        ui->xLabel->setText("R"); ui->yLabel->setText("G"); ui->zLabel->setText("B"); break;
    case QColor::Hsl: colorSetter = &QColor::setHsl; setHslTootip();
        X = clr.hslHue(); Y = clr.hslSaturation(); Z = clr.lightness(); setMaxX(359);
        ui->xLabel->setText("H"); ui->yLabel->setText("S"); ui->zLabel->setText("L"); break;
    case QColor::Hsv: colorSetter = &QColor::setHsv; setHsvTootip();
        X = clr.hsvHue(); Y = clr.hsvSaturation(); Z = clr.value(); setMaxX(359);
        ui->xLabel->setText("H"); ui->yLabel->setText("S"); ui->zLabel->setText("V"); break;
    default: break; }

    setX(X); setY(Y); setZ(Z);
}

void ColorSetter::updateColor()
{ (clr.spec() != QColor::Cmyk) ? ((clr.*colorSetter)(X,Y,Z,A)) : (clr.setCmyk(X,Y,Z,K,A)); emit colorChanged(clr); }

void ColorSetter::setMaxX(int max)
{ ui->xSlider->setMaximum(max); ui->xSpin->setMaximum(max); }

void ColorSetter::hideK()
{ ui->kLabel->hide(); ui->kSlider->hide(); ui->kSpin->hide(); }

void ColorSetter::showK()
{ ui->kLabel->show(); ui->kSlider->show(); ui->kSpin->show(); }
