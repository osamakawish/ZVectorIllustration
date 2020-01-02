#ifndef POINTF_H
#define POINTF_H

#include <QPointF>

class PointF : public QPointF
{
public:
    PointF();
    PointF(qreal xpos, qreal ypos);

    PointF unitize();
};

#endif // POINTF_H
