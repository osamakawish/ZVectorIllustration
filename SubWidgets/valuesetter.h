#ifndef VALUESETTER_H
#define VALUESETTER_H

#include <QWidget>

namespace Ui {
class ValueSetter;
}

class ValueSetter : public QWidget
{
    Q_OBJECT

public:
    explicit ValueSetter(QWidget *parent = nullptr);
    ~ValueSetter();

private:
    Ui::ValueSetter *ui;
};

#endif // VALUESETTER_H
