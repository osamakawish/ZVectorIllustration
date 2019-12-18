#include "filewidget.h"
#include "ui_filewidget.h"
#include <iostream>
#include <set>
#include <QSet>

FileWidget::FileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);

}

FileWidget::~FileWidget()
{
    delete ui;
}

QTabWidget &FileWidget::tabWidget()
{
    return *ui->tabWidget;
}

void FileWidget::newFile()
{
    QTabWidget *tabs = ui->tabWidget;
    QString untitled = "Untitled"; int j = 0;
    QSet<QString> untitledNames; QString tabText;
    for (int i=0;i<tabs->count();i++) {
        tabText = tabs->tabText(i);
        if (tabText.startsWith(untitled)) {untitledNames.insert(tabText);}
    }
    while (!untitledNames.contains(untitled+QString(j)) && j<tabs->count()) {j++;}
    tabs->addTab(new QGraphicsView(this),untitled+QString(j));
}
