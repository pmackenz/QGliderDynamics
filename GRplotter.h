#ifndef GRPLOTTER_H
#define GRPLOTTER_H

#include "qcp/qcustomplot.h"

class GRplotter:
    public QWidget
{
public:
    GRplotter(QWidget* parent);
    ~GRplotter();

    void setSpeeds(float sink, float air, float ground);

private:

    void refresh();

    float sink   = 1.0;
    float air    = 6.0;
    float ground = 6.0;

    QCustomPlot* plot = nullptr;
};

#endif // GRPLOTTER_H
