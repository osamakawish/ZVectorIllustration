#include "radiobuttongrid.h"
#include "ui_radiobuttongrid.h"

#include <QRadioButton>
#include <QLayout>
#include <QDebug>

RadioButtonGrid::RadioButtonGrid(QWidget *parent, int x, int y) :
    QWidget(parent),
    ui(new Ui::RadioButtonGrid)
{
    ui->setupUi(this);
    setSize(x,y);
}

RadioButtonGrid::~RadioButtonGrid()
{
    delete ui;
}

void RadioButtonGrid::setSize(int x, int y)
{
    layout()->setSizeConstraint(QLayout::SetNoConstraint);
    clearGrid();
    for (int row=0; row<x; row++) {
        for (int col=0; col<y; col++) {
            QRadioButton *radiobutton = new QRadioButton();
            ui->gridLayout->addWidget(radiobutton,row,col);
            connect(radiobutton,&QRadioButton::pressed,this,
                    [=](){radiobutton->blockSignals(true);check(row,col);radiobutton->blockSignals(false);});
        }
    }

    if (x > 1 && y > 1) check(0,0);
    adjustSize(); layout()->setSizeConstraint(QLayout::SetFixedSize);
}

void RadioButtonGrid::check(int x, int y)
{ if (itemAt(x,y)->isEnabled()) {itemAt(x,y)->setChecked(true); checkedX=x; checkedY=y;
enable(); edgeSignals(x,y); emit buttonChecked(x,y);} }

void RadioButtonGrid::disable(int x, int y)
{
    QRadioButton *button = itemAt(x,y);
    if (button->isChecked()) {return;}

    enable(); button->setEnabled(false);
    disabledX = x; disabledY = y; hasDisabledButton = true;
}

void RadioButtonGrid::enable()
{
    for (int x=0; x<xLength(); ++x) {
        for (int y=0; y<yLength(); ++y) {
            itemAt(x,y)->setEnabled(true);
        }
    }
}

int RadioButtonGrid::xLength()
{ return ui->gridLayout->columnCount(); }

int RadioButtonGrid::yLength()
{ return ui->gridLayout->rowCount(); }

void RadioButtonGrid::restrictMutualEdges(RadioButtonGrid *other)
{ connect(this,&RadioButtonGrid::extremeChecked,other,&RadioButtonGrid::restrictOnlyEdges);
connect(other,&RadioButtonGrid::extremeChecked,this,&RadioButtonGrid::restrictOnlyEdges); }

void RadioButtonGrid::restrictBottom()
{ for (int x=0; x<xLength(); x++) { itemAt(x,0)->setEnabled(false); } }

void RadioButtonGrid::restrictLeft()
{ for (int y=0; y<yLength(); y++) { itemAt(0,y)->setEnabled(false); } }

void RadioButtonGrid::restrictTop()
{ for (int x=0; x<xLength(); x++) { itemAt(x,yLength()-1)->setEnabled(false); } }

void RadioButtonGrid::restrictRight()
{ for (int y=0; y<xLength(); y++) { itemAt(xLength()-1,y)->setEnabled(false); } }

void RadioButtonGrid::edgeSignals(int x, int y)
{
    enable();

    Extreme X, Y;

    if (x==0) {X = Extreme::MIN;} else if (x==xLength()-1) {X = Extreme::MAX;} else {X = Extreme::MID;}
    if (y==0) {Y = Extreme::MIN;} else if (y==yLength()-1) {Y = Extreme::MAX;} else {Y = Extreme::MID;}

    emit extremeChecked(X,Y);
}

void RadioButtonGrid::restrictOnlyEdges(Extreme x, Extreme y)
{
    if (x == Extreme::MIN) {restrictLeft();} else if (x == Extreme::MAX) {restrictRight();}
    if (y == Extreme::MIN) {restrictBottom();} else if (y == Extreme::MAX) {restrictTop();}
    updatedCheckedBox(x,y);
}

// Note: these are the restricted extremes. Opposite extremes need to be checked.
void RadioButtonGrid::updatedCheckedBox(Extreme x, Extreme y)
{
    if ((x==Extreme::MID && y==Extreme::MID)) { enable(); return; }
    else if (!currentCheckedInExtreme(x,y)) {return;}

    int X, Y;
    if (x == Extreme::MIN) {X = xLength()-1;} else if (x == Extreme::MAX) {X = 0;} else {X=checkedX;}
    if (y == Extreme::MIN) {Y = xLength()-1;} else if (y == Extreme::MAX) {Y = 0;} else {Y=checkedY;}

    itemAt(X,Y)->setChecked(true); checkedX = X; checkedY =Y; emit buttonChecked(X,Y);
}

bool RadioButtonGrid::currentCheckedInExtreme(Extreme x, Extreme y)
{
    return ((x == Extreme::MIN && checkedX == 0) || (x == Extreme::MAX && checkedX == xLength()-1)) ||
           ((y == Extreme::MIN && checkedY == 0) || (y == Extreme::MAX && checkedY == yLength()-1));
}

QRadioButton *RadioButtonGrid::itemAt(int x, int y)
{ return dynamic_cast<QRadioButton *>(ui->gridLayout->itemAtPosition(x,y)->widget()); }

void RadioButtonGrid::clearGrid()
{ foreach (QRadioButton *radioButton, findChildren<QRadioButton *>()) { delete radioButton; } }
