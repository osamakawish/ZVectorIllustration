#include "valuesetter.h"
#include "ui_valuesetter.h"

ValueSetter::ValueSetter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ValueSetter)
{
    ui->setupUi(this);
}

ValueSetter::~ValueSetter()
{
    delete ui;
}
