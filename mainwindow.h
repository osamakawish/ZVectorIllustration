#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Windows/helpwindow.h"
#include "Windows/settingswindow.h"

#include <memory>

#include <QMainWindow>
#include <QFileDialog>
#include <QActionGroup>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QActionGroup graphicsActionGroup;

    std::unique_ptr<HelpWindow> helpWindow;
    std::unique_ptr<SettingsWindow> settingsWindow;

    void fileDialog(QFileDialog::AcceptMode mode);

    void openFileDialog(); void openFile(int i);
    void saveFileDialog(); void saveFile(int i);

    void prepareWindows();
    void prepareMenuActions();
    void prepareGraphicsActions(); void connectGraphicsActions();

    void mouseShape(); void mouseVector(); void penShape(); void penVector();
    void textShape(); void textVector(); void zoomShape(); void zoomVector();

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
