#include "FlightPath.h"
#include "ui_FlightPath2.h"

#include <QString>
#include <QVector2D>
#include <QtMath>

#include <QDebug>

FlightPath::FlightPath(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FlightPath2)
{
    ui->setupUi(this);

    ui->gliderDir->setRange(-180/STEP,180/STEP);
    ui->gliderDir->setSingleStep(STEP);
    ui->windDir->setRange(-180/STEP,180/STEP);
    ui->windDir->setSingleStep(STEP);

    ui->gliderSpeed->setRange(15,30);
    ui->windSpeed->setRange(0,20);

    createConnections();
    setDefaultValues();
}

FlightPath::~FlightPath()
{
    delete ui;
}

void FlightPath::createConnections()
{

}

void FlightPath::setDefaultValues()
{
    ui->gliderDir->setValue(90/STEP);
    ui->windDir->setValue(45/STEP);
    ui->gliderDir->setWrapping(true);
    ui->windDir->setWrapping(true);
    ui->gliderSpeed->setValue(24);
    ui->windSpeed->setValue(10);
}

void FlightPath::on_gliderDir_valueChanged(int val)
{
    int dir = STEP*val;

    while (dir < 0) { dir += 360; }

    QString s = QString("%1").arg(dir);

    //qDebug() << "on_gliderDir_valueChanged:" << dir << "->" << s ;

    ui->gliderDir_LE->setText(s);
    update();
}

void FlightPath::on_windDir_valueChanged(int val)
{
    int dir = STEP*val;

    while (dir < 0) { dir += 360; }

    QString s = QString("%1").arg(dir);

    //qDebug() << "on_windDir_valueChanged:" << dir << "->" << s ;

    ui->windDir_LE->setText(s);
    update();
}

void FlightPath::on_gliderSpeed_valueChanged(int val)
{
    QString s = QString("%1").arg(val);

    //qDebug() << "on_gliderSpeed_valueChanged:" << val << "->" << s ;

    ui->gliderSpeed_LE->setText(s);
    update();
}

void FlightPath::on_windSpeed_valueChanged(int val)
{
    QString s = QString("%1").arg(val);

    //qDebug() << "on_windSpeed_valueChanged:" << val << "->" << s ;

    ui->windSpeed_LE->setText(s);
    update();
}

void FlightPath::on_glider_GR_currentIndexChanged(int idx)
{
    Q_UNUSED(idx)

    //qDebug() << "on_glider_GR_currentIndexChanged:" << idx ;

    update();
}

void FlightPath::update()
{
    float glider_GR = (ui->glider_GR->currentText()).toFloat();

    float glider_speed = 0.0;
    float glider_dir   = 0.0;
    float wind_speed   = 0.0;
    float wind_dir     = 0.0;


    if ( !(ui->gliderSpeed_LE->text()).isEmpty() )
    { glider_speed = (ui->gliderSpeed_LE->text()).toFloat(); }

    if ( !(ui->gliderDir_LE->text()).isEmpty() )
    {
        glider_dir = (ui->gliderDir_LE->text()).toFloat();
        glider_dir *= STEP;
    }

    if ( !(ui->windSpeed_LE->text()).isEmpty() )
    { wind_speed = (ui->windSpeed_LE->text()).toFloat(); }

    if ( !(ui->windDir_LE->text()).isEmpty() )
    {
        wind_dir = (ui->windDir_LE->text()).toFloat();
        wind_dir *= STEP;
    }


    QVector2D glider_velocity = QVector2D( glider_speed*sin(qDegreesToRadians(glider_dir)), glider_speed*cos(qDegreesToRadians(glider_dir)) );

    ui->groundView->setGliderVelocity(glider_velocity);

    QVector2D wind_velocity   = QVector2D( wind_speed*sin(qDegreesToRadians(wind_dir)), wind_speed*cos(qDegreesToRadians(wind_dir)) );

    ui->groundView->setWindVelocity(wind_velocity);

    QVector2D ground_velocity = glider_velocity + wind_velocity;

    float ground_speed   = ground_velocity.length();
    float ground_bearing = qRadiansToDegrees( atan2(ground_velocity[0], ground_velocity[1]) );

    while (ground_bearing < 0) { ground_bearing += 360; }

    float ground_GR = glider_GR * ground_speed / glider_speed;

    ui->flight_path_speed_LE->setText(QString("%1").arg(ground_speed,0,'f',1));
    ui->flight_path_bearing_LE->setText(QString("%1").arg(ground_bearing,0,'f',0));
    ui->flight_path_GR_LE->setText(QString("%1").arg(ground_GR,0,'f',1));

    ui->sideView->setSpeeds(1.0, glider_GR, ground_GR);
}
