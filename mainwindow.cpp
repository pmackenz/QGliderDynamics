#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "FlightPath.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(new FlightPath());
}

MainWindow::~MainWindow()
{
    delete ui;
}

