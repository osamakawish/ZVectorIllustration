#ifndef RADIOBUTTONGRID_H
#define RADIOBUTTONGRID_H

#include <QWidget>

enum class Extreme {MIN=-1, MID, MAX};

class QRadioButton;

namespace Ui {
class RadioButtonGrid;
}

class RadioButtonGrid : public QWidget
{
    Q_OBJECT

public:
    explicit RadioButtonGrid(QWidget *parent = nullptr, int x=0, int y=0);
    ~RadioButtonGrid();

    void setSize(int x, int y);
    void check(int x, int y);
    void disable(int x, int y);
    void enable();

    QRadioButton *checkedButton();

    int xLength();
    int yLength();

    //! Restricts this and other grid from having points that are part of the same edge
    void restrictMutualEdges(RadioButtonGrid *other);

signals:
    void extremeChecked(Extreme x, Extreme y);
    void buttonChecked(int x, int y);

private:
    void restrictTop();
    void restrictLeft();
    void restrictBottom();
    void restrictRight();
    void edgeSignals(int x, int y);
    void restrictOnlyEdges(Extreme x, Extreme y);
    void updatedCheckedBox(Extreme x, Extreme y);
    bool currentCheckedInExtreme(Extreme x, Extreme y);

    int checkedX, checkedY;
    QRadioButton *itemAt(int x, int y);
    void clearGrid();

    Ui::RadioButtonGrid *ui;

};

#endif // RADIOBUTTONGRID_H
