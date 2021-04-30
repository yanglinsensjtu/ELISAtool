#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Determinant * D = new Determinant();
    QVector<int> V = D->inivec(4);

    D->Perm(V,0,3);
}

MainWindow::~MainWindow()
{
    delete ui;
}


