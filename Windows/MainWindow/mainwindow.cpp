#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

#include "ActionMethods/mousebehaviour.h"
#include "ActionMethods/mouseaction.h"
#include "ActionMethods/penaction.h"
#include "ActionMethods/textaction.h"
#include "ActionMethods/zoomaction.h"

#include "MainWidgets/graphicsview.h"

//! @note Need to change all the triggered to toggled, and make sure to deal with cases where it's false.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , graphicsActionGroup(this) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prepareWindows();
    prepareMenuActions();
    prepareGraphicsActions();
    setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fileDialog(QFileDialog::AcceptMode mode)
{
    QFileDialog *dialog = new QFileDialog(this);
    dialog->setAcceptMode(mode); dialog->show();

    switch (mode) {
    case QFileDialog::AcceptOpen:
        connect(dialog,&QFileDialog::finished,this,&MainWindow::openFile); return;
    case QFileDialog::AcceptSave:
        connect(dialog,&QFileDialog::finished,this,&MainWindow::saveFile); return;
    }
}

void MainWindow::openFileDialog()
{ fileDialog(QFileDialog::AcceptOpen); }

void MainWindow::openFile(int i)
{
    // Redirected from openFileDialog(int)
    switch (i) {
    case 0: return;
    case 1: return;
    }
}

void MainWindow::saveFileDialog()
{ fileDialog(QFileDialog::AcceptSave); }

void MainWindow::saveFile(int i)
{
    switch (i) {
    case 0: return;
    case 1: return;
    }
}

void MainWindow::prepareWindows()
{
    helpWindow = std::unique_ptr<HelpWindow>(new HelpWindow(this));
    connect(ui->actionHelp,&QAction::triggered,helpWindow.get(),&HelpWindow::show,Qt::UniqueConnection);
    settingsWindow = std::unique_ptr<SettingsWindow>(new SettingsWindow(this));
    connect(ui->actionOptions,&QAction::triggered,settingsWindow.get(),&SettingsWindow::show,Qt::UniqueConnection);
}

void MainWindow::prepareMenuActions()
{
    connect(ui->actionNew,&QAction::triggered,ui->fileWidget,&FileWidget::newFile,Qt::UniqueConnection);
    connect(ui->actionOpen_Import,&QAction::triggered,this,&MainWindow::openFileDialog);
    connect(ui->actionSave_Export,&QAction::triggered,this,&MainWindow::saveFileDialog);
}

void MainWindow::prepareGraphicsActions()
{
    ui->actionShape_Mouse->trigger();
    graphicsActionGroup.addAction(ui->actionShape_Mouse); graphicsActionGroup.addAction(ui->actionShape_Pen);
    graphicsActionGroup.addAction(ui->actionShape_Text); graphicsActionGroup.addAction(ui->actionShape_Zoom);
    graphicsActionGroup.addAction(ui->actionVector_Mouse); graphicsActionGroup.addAction(ui->actionVector_Pen);
    graphicsActionGroup.addAction(ui->actionVector_Text); graphicsActionGroup.addAction(ui->actionVector_Zoom);

    connectGraphicsActions();
}

void MainWindow::connectGraphicsActions()
{
    /// Note: Need to add view->setMouseTracking(true/false) to graphics views,
    /// depending on the action selected.
    connect(ui->actionShape_Mouse,&QAction::toggled,this,&MouseAction::shapeToggle);
    connect(ui->actionVector_Mouse,&QAction::toggled,this,&MouseAction::vectorToggle);

    connect(ui->actionShape_Pen,&QAction::toggled,this,&PenAction::shapeToggle);
    connect(ui->actionVector_Pen,&QAction::toggled,this,&PenAction::vectorToggle);

    connect(ui->actionShape_Text,&QAction::toggled,this,&TextAction::shapeToggle);
    connect(ui->actionVector_Text,&QAction::toggled,this,&TextAction::vectorToggle);

    connect(ui->actionShape_Zoom,&QAction::toggled,this,&ZoomAction::shapeToggle);
    connect(ui->actionVector_Zoom,&QAction::toggled,this,&ZoomAction::vectorToggle);
}
