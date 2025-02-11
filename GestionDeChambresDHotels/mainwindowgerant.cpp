#include "mainwindowgerant.h"
#include "ui_mainwindowgerant.h"

MainWindowGerant::MainWindowGerant(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindowGerant)
{
    ui->setupUi(this);
}

MainWindowGerant::~MainWindowGerant()
{
    delete ui;
}
