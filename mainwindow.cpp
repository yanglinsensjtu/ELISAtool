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
    QVector<QVector<int>> vec_seq;
    D->Perm(V,&vec_seq,0,3);
    qDebug()<< vec_seq<< vec_seq.size();
}

MainWindow::~MainWindow()
{
    delete ui;
}


