#include "propertywidget.h"
#include "ui_propertywidget.h"
#include <QDebug>

PropertyWidget::PropertyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PropertyWidget)
{
    ui->setupUi(this);
    connect(ui->colorModelSelect,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this,[=](int i){ui->strokeColor->setSpec(spec(i));});

    ui->originSelectGrid->setSize(3,3);
    ui->axesDirectionSelectGrid->setSize(2,2);
    ui->originSelectGrid->check(0,0);
    ui->axesDirectionSelectGrid->check(1,1);

    ui->originSelectGrid->restrictMutualEdges(ui->axesDirectionSelectGrid);

    ui->dpiSetter->setDecimals(0); ui->dpiSetter->setUnits("px / in");
}

PropertyWidget::~PropertyWidget()
{
    delete ui;
}

QColor::Spec PropertyWidget::spec(int index)
{
    switch (index) {
    case 0: return QColor::Rgb;
    case 1: return  QColor::Cmyk;
    case 2: return QColor::Hsl;
    case 3: return QColor::Hsv;
    default: return QColor::Invalid;
    }
}
