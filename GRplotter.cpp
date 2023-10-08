#include "GRplotter.h"
#include <QVBoxLayout>

GRplotter::GRplotter(QWidget* parent):
    QWidget(parent)
{
    plot = new QCustomPlot();
    QVBoxLayout *lyt = new QVBoxLayout(this);
    lyt->setContentsMargins(0,0,0,0);
    lyt->addWidget(plot);

    refresh();
}


void GRplotter::setSpeeds(float sink, float air, float ground)
{
    this->sink   = sink;
    this->air    = air;
    this->ground = ground;

    refresh();
}

GRplotter::~GRplotter()
{
    delete plot;
}

void GRplotter::refresh()
{
    plot->clearItems();
    plot->clearGraphs();
    plot->clearPlottables();

    QVector<double> x(2), y(2);

    // create a title

    if (plot->plotLayout()->rowCount() == 1)
    {
        // first we create and prepare a text layout element:
        QCPTextElement *title = new QCPTextElement(plot);
        title->setText("Glide Ratio (GR)");
        title->setFont(QFont("sans", 12, QFont::Bold));

        // then we add it to the main plot layout:
        plot->plotLayout()->insertRow(0); // insert an empty row above the axis rect
        plot->plotLayout()->addElement(0, 0, title); // place the title in the empty cell we've just created
    }

    // no wind

    plot->addGraph();

    x[0] = 0.0;
    x[1] = air;

    y[0] = sink;
    y[1] = 0.0;

    plot->graph(0)->addData(x,y);
    QPen pen;
    pen.setColor(Qt::green);
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    plot->graph(0)->setPen(pen);
    plot->graph(0)->setName("no wind");

    // with wind

    plot->addGraph();

    x[0] = 0.0;
    x[1] = ground;

    y[0] = sink;
    y[1] = 0.0;

    plot->graph(1)->addData(x,y);
    QPen pen1;
    pen1.setColor(Qt::red);
    pen1.setStyle(Qt::SolidLine);
    pen1.setWidth(3);
    plot->graph(1)->setPen(pen1);
    plot->graph(1)->setName("with wind");


    double range = air>ground ? air : ground;
    plot->yAxis->setRange(0.0, sink);
    plot->xAxis->setRange(0.0, range);

    plot->xAxis->rescale();
    plot->yAxis->rescale();

    plot->legend->setVisible(true);

    plot->replot();
}
