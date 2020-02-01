#ifndef FILEWIDGET_H
#define FILEWIDGET_H

#include <QWidget>
#include <QTabWidget>

namespace Ui {
class FileWidget;
}

class FileWidget : public QWidget
{
    Q_OBJECT

    void tabChange(int index);

public:
    explicit FileWidget(QWidget *parent = nullptr);
    ~FileWidget();

    QTabWidget &tabWidget();
    void newFile();

private:
    Ui::FileWidget *ui;
};

#endif // FILEWIDGET_H
