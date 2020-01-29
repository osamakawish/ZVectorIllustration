#include "filewidget.h"
#include "GraphicsView/graphicsview.h"
#include "ui_filewidget.h"
#include <iostream>
#include <set>
#include <QSet>
#include <QDebug>

#include "ActionMethods/mousebehaviour.h"

FileWidget::FileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);

    newFile();
    // Update MouseBehaviour view when tab changes.
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,[&](){
        MouseBehaviour::setView(dynamic_cast<GraphicsView *>(ui->tabWidget->currentWidget()));
    });

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
    GraphicsView *view = new GraphicsView(this);
    tabs->addTab(view,untitled+QString::number(j));
    tabs->setCurrentWidget(view);
}
