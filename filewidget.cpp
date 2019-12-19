#include "filewidget.h"
#include "graphicsview.h"
#include "ui_filewidget.h"
#include <iostream>
#include <set>
#include <QSet>
#include <QDebug>

FileWidget::FileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);
    newFile();
    delete ui->tabWidget->widget(0);
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
    tabs->addTab(new GraphicsView(this),untitled+QString::number(j));
}
