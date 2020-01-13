#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QWidget>

namespace Ui {
class PropertyWidget;
}

class PropertyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PropertyWidget(QWidget *parent = nullptr);
    ~PropertyWidget();

private:
    QColor::Spec spec(int index);
    void checkOriginButton(int x, int y);
    void checkAxesDirectionButton(int x, int y);

    Ui::PropertyWidget *ui;
};

#endif // PROPERTYWIDGET_H
