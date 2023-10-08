#include "Plotter.h"
#include <QVBoxLayout>
#include <QVector>

Plotter::Plotter(QWidget* parent) :
    QWidget(parent)
{
    plot = new QCustomPlot();
    QVBoxLayout *lyt = new QVBoxLayout(this);
    lyt->setContentsMargins(0,0,0,0);
    lyt->addWidget(plot);
}

Plotter::~Plotter()
{
    delete plot;
}

void Plotter::setGliderVelocity(QVector2D &vel)
{
    glider_velocity = vel;
    refresh();
}

void Plotter::setWindVelocity(QVector2D &vel)
{
    wind_velocity = vel;
    refresh();
}

void Plotter::setLimits(float maxX, float maxY)
{
    plot->xAxis->setRange(-maxX, maxX);
    plot->yAxis->setRange(-maxY, maxY);
}

void Plotter::refresh()
{
    plot->clearItems();
    plot->clearGraphs();
    plot->clearPlottables();

    QVector2D ground_velocity = glider_velocity + wind_velocity;
    QVector2D referencePos    = position + 0.75*ground_velocity;

    drawGlider(referencePos, glider_velocity);

    //
    // plot glider velocity
    //
    QVector<float> x;
    QVector<float> y;
    QVector<QVector2D> V;

    x.append( position[0] );
    y.append( position[1] );

    V.append( glider_velocity );

    // add the arrow:
    QCPItemLine *gliderDir = new QCPItemLine(plot);
    gliderDir->setPen(QPen(Qt::green));
    gliderDir->start->setCoords(0.0, 0.0);
    gliderDir->end->setCoords(glider_velocity[0], glider_velocity[1]);
    gliderDir->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemLine *gliderDir2 = new QCPItemLine(plot);
    gliderDir2->setPen(QPen(Qt::green, 1, Qt::PenStyle::DashLine));
    gliderDir2->start->setCoords(wind_velocity[0], wind_velocity[1]);
    gliderDir2->end->setCoords(ground_velocity[0], ground_velocity[1]);
    gliderDir2->setHead(QCPLineEnding::esSpikeArrow);

    //
    // plot wind velocity
    //
    x.append( position[0] + glider_velocity[0] );
    y.append( position[1] + glider_velocity[1] );
    //#self.axes.plot(x,y, '-b', lw=2, label="wind drift")

    // add the arrow:
    QCPItemLine *windDir = new QCPItemLine(plot);
    windDir->setPen(QPen(Qt::blue));
    windDir->start->setCoords(0.0, 0.0);
    windDir->end->setCoords(wind_velocity[0], wind_velocity[1]);
    windDir->setHead(QCPLineEnding::esSpikeArrow);

    QCPItemLine *windDir2 = new QCPItemLine(plot);
    windDir2->setPen(QPen(Qt::blue, 1, Qt::PenStyle::DashLine));
    windDir2->start->setCoords(glider_velocity[0], glider_velocity[1]);
    windDir2->end->setCoords(ground_velocity[0], ground_velocity[1]);
    windDir2->setHead(QCPLineEnding::esSpikeArrow);

    //
    // plot ground velocity
    //
    x.append( position[0] );
    y.append( position[1] );
    V.append( ground_velocity );

    double a = 0.0;
    double b = 1.0;

    // add the arrow:
    QCPItemLine *gliderPath = new QCPItemLine(plot);
    gliderPath->setPen(QPen(Qt::red, 3));
    gliderPath->start->setCoords(a*ground_velocity[0], a*ground_velocity[1]);
    gliderPath->end->setCoords(b*ground_velocity[0], b*ground_velocity[1]);
    gliderPath->setHead(QCPLineEnding::esSpikeArrow);

    gliderPath->setObjectName("ground arrow");

    //QCPPlottableLegendItem *gliderPathItem = new QCPPlottableLegendItem(plot, gliderPath);
    //plot->legend->addItem(gliderPathItem);

    gliderPath = new QCPItemLine(plot);
    gliderPath->setPen(QPen(Qt::red, 2, Qt::DashLine));
    a = 1.05; b = 1.25;
    gliderPath->start->setCoords(a*ground_velocity[0], a*ground_velocity[1]);
    gliderPath->end->setCoords(b*ground_velocity[0], b*ground_velocity[1]);
    gliderPath->setHead(QCPLineEnding::esSpikeArrow);

    gliderPath = new QCPItemLine(plot);
    gliderPath->setPen(QPen(Qt::red, 1.5, Qt::DashLine));
    a = 1.3; b = 1.45;
    gliderPath->start->setCoords(a*ground_velocity[0], a*ground_velocity[1]);
    gliderPath->end->setCoords(b*ground_velocity[0], b*ground_velocity[1]);
    gliderPath->setHead(QCPLineEnding::esSpikeArrow);

    gliderPath = new QCPItemLine(plot);
    gliderPath->setPen(QPen(Qt::red, 1., Qt::DashLine));
    a = 1.5; b = 1.6;
    gliderPath->start->setCoords(a*ground_velocity[0], a*ground_velocity[1]);
    gliderPath->end->setCoords(b*ground_velocity[0], b*ground_velocity[1]);
    gliderPath->setHead(QCPLineEnding::esSpikeArrow);


    plot->addGraph();

    QVector<double> xp(1), yp(1);
    xp[0] = position[0];
    yp[0] = position[1];
    plot->graph()->setData(xp, yp);
    plot->graph()->setPen(QPen(Qt::black));
    plot->graph()->removeFromLegend();

    setLimits(60,50);
    //#self.axes.set_axis_off()
    plot->yAxis->setScaleRatio(plot->xAxis, 1.0);
    plot->xAxis->grid()->setVisible(true);
    plot->yAxis->grid()->setVisible(true);

    //
    // legend
    //
    plot->addGraph();
    plot->graph()->setName("in air");
    plot->graph()->setPen(QPen(Qt::green, 2));

    plot->addGraph();
    plot->graph()->setName("wind");
    plot->graph()->setPen(QPen(Qt::blue, 2));

    plot->addGraph();
    plot->graph()->setName("above ground");
    plot->graph()->setPen(QPen(Qt::red, 3));


    // custom_lines = [Line2D([0], [0], color='green', lw=2), Line2D([0], [0], color='blue',  lw=2), Line2D([0], [0], color='red',   lw=2)];

    // plot->axes.legend(custom_lines, ("in air","wind","ground"), bbox_to_anchor=(1.00, 0.50), loc='center left');

    plot->legend->setVisible(true);
    plot->replot();
}

void Plotter::drawGlider(QVector2D &x0, QVector2D &dir)
{
        /*
        :param x0:  a vector defining the glider plot position
        :param dir: a vector pointing in the glider direction
        */

        double w = 20.;
        double d =  6.;

        QVector2D normDir = dir.normalized();
        QVector2D normPerp(-normDir[1], normDir[0]);

        QVector<double> x, y;

        x.append(x0[0] - w/2 * normPerp[0]); y.append(x0[1] - w/2 * normPerp[1]);
        x.append(x0[0] + w/2 * normPerp[0]); y.append(x0[1] + w/2 * normPerp[1]);

        for(double t = w/2; t >= -w/2;  t -= w/10.)
        {
            double s = -d*(1. - 2.0*pow((t/w),2.));

            QVector2D pt0 = x0 +   s * normDir + t * normPerp;
            QVector2D pt1 = x0 + 0.0 * normDir + t * normPerp;

            x.append( pt0[0] );  y.append( pt0[1] );
            x.append( pt1[0] );  y.append( pt1[1] );
            x.append( pt0[0] );  y.append( pt0[1] );
        }

        QCPCurve *curve = new QCPCurve(plot->xAxis, plot->yAxis);
        curve->addData(x, y);
        curve->setPen(QPen(Qt::magenta, 2));
        curve->removeFromLegend();
}

