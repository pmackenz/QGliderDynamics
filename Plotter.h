#ifndef PLOTTER_H
#define PLOTTER_H

#include "qcp/qcustomplot.h"

#include <QVector2D>

class Plotter:
    public QWidget
{
public:
    Plotter(QWidget* parent);
    ~Plotter();

    void setGliderVelocity(QVector2D &vel);
    void setWindVelocity(QVector2D &vel);
    void setLimits(float maxX, float maxY);

private:

    void refresh();
    void drawGlider(QVector2D &x0, QVector2D &dir);

    QVector2D glider_velocity = QVector2D(24,0);
    QVector2D wind_velocity   = QVector2D(0,0);
    QVector2D position        = QVector2D(0,0);

    QCustomPlot* plot = nullptr;
};

#endif // PLOTTER_H

