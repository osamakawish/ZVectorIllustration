#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    prepareWindows();
    prepareMenuActions();
}

MainWindow::~MainWindow()
{
    delete ui;
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
}

