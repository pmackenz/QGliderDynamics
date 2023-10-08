#ifndef FLIGHTPATH_H
#define FLIGHTPATH_H

#include <QWidget>

namespace Ui {
class FlightPath;
}

class FlightPath : public QWidget
{
    Q_OBJECT

public:
    explicit FlightPath(QWidget *parent = nullptr);
    ~FlightPath();

private:
    Ui::FlightPath *ui;

    const int STEP = 1;

    void createConnections();
    void setDefaultValues();
    void update();

private slots:
    void on_gliderDir_valueChanged(int val);
    void on_windDir_valueChanged(int val);
    void on_gliderSpeed_valueChanged(int val);
    void on_windSpeed_valueChanged(int val);
    void on_glider_GR_currentIndexChanged(int idx);
};

#endif // FLIGHTPATH_H
