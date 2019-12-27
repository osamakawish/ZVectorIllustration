#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "ActionMethods/mousebehaviour.h"
#include "ActionMethods/mouseaction.h"
#include "ActionMethods/penaction.h"
#include "ActionMethods/textaction.h"
#include "ActionMethods/zoomaction.h"

#include "graphicsview.h"

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
    connect(ui->actionShape_Mouse,&QAction::triggered,this,&MainWindow::mouseShape);
    connect(ui->actionVector_Mouse,&QAction::triggered,this,&MainWindow::mouseVector);

    connect(ui->actionShape_Mouse,&QAction::triggered,this,&MainWindow::penShape);
    connect(ui->actionVector_Mouse,&QAction::triggered,this,&MainWindow::penVector);

    connect(ui->actionShape_Mouse,&QAction::triggered,this,&MainWindow::textShape);
    connect(ui->actionVector_Mouse,&QAction::triggered,this,&MainWindow::textVector);

    connect(ui->actionShape_Mouse,&QAction::triggered,this,&MainWindow::zoomShape);
    connect(ui->actionVector_Mouse,&QAction::triggered,this,&MainWindow::zoomVector);
}

void MainWindow::mouseShape()
{
    GraphicsView::Press = &MouseAction::shapePress;
    GraphicsView::DoubleClick = &MouseAction::shapeDoubleClick;
    GraphicsView::Move = &MouseAction::shapeMove;
    GraphicsView::Release = &MouseAction::shapeRelease;
}

void MainWindow::mouseVector()
{
    GraphicsView::Press = &MouseAction::vectorPress;
    GraphicsView::DoubleClick = &MouseAction::vectorDoubleClick;
    GraphicsView::Move = &MouseAction::vectorMove;
    GraphicsView::Release = &MouseAction::vectorRelease;
}

void MainWindow::penShape()
{
    GraphicsView::Press = &PenAction::shapePress;
    GraphicsView::DoubleClick = &PenAction::shapeDoubleClick;
    GraphicsView::Move = &PenAction::shapeMove;
    GraphicsView::Release = &PenAction::shapeRelease;
}

void MainWindow::penVector()
{
    GraphicsView::Press = &PenAction::vectorPress;
    GraphicsView::DoubleClick = &PenAction::vectorDoubleClick;
    GraphicsView::Move = &PenAction::vectorMove;
    GraphicsView::Release = &PenAction::vectorRelease;
}

void MainWindow::textShape()
{
    GraphicsView::Press = &TextAction::shapePress;
    GraphicsView::DoubleClick = &TextAction::shapeDoubleClick;
    GraphicsView::Move = &TextAction::shapeMove;
    GraphicsView::Release = &TextAction::shapeRelease;
}

void MainWindow::textVector()
{
    GraphicsView::Press = &TextAction::vectorPress;
    GraphicsView::DoubleClick = &TextAction::vectorDoubleClick;
    GraphicsView::Move = &TextAction::vectorMove;
    GraphicsView::Release = &TextAction::vectorRelease;
}

void MainWindow::zoomShape()
{
    GraphicsView::Press = &ZoomAction::shapePress;
    GraphicsView::DoubleClick = &ZoomAction::shapeDoubleClick;
    GraphicsView::Move = &ZoomAction::shapeMove;
    GraphicsView::Release = &ZoomAction::shapeRelease;
}

void MainWindow::zoomVector()
{
    GraphicsView::Press = &ZoomAction::vectorPress;
    GraphicsView::DoubleClick = &ZoomAction::vectorDoubleClick;
    GraphicsView::Move = &ZoomAction::vectorMove;
    GraphicsView::Release = &ZoomAction::vectorRelease;
}

