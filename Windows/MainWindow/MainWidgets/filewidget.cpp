#include "filewidget.h"
#include "GraphicsView/graphicsview.h"
#include "ui_filewidget.h"
#include <iostream>
#include <set>
#include <QSet>
#include <QDebug>

#include "ActionMethods/mousebehaviour.h"
#include "ActionMethods/mouseaction.h"

void FileWidget::tabChange(int index)
{
    GraphicsView *view = dynamic_cast<GraphicsView *>(ui->tabWidget->widget(index));
    Mouse::setView(view);
    MouseAction::NODE_VECTOR_SELECTION = &view->NODE_VECTOR_SELECTION;
    MouseAction::SHAPE_CURVE_SELECTION = &view->SHAPE_CURVE_SELECTION;
}

FileWidget::FileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileWidget)
{
    ui->setupUi(this);

    newFile();
    // Update MouseBehaviour view when tab changes.
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&FileWidget::tabChange);

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
