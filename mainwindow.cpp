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
    QVector<int> V = D->inivec(5);
    QVector<QVector<int>> vec_seq;
    D->Perm(V,&vec_seq,0,V.size()-1);
    qDebug()<< vec_seq[1]<< vec_seq.size() << D->Iseven(2)<<D->PowerIsPosition(vec_seq[1]);
}

MainWindow::~MainWindow()
{
    delete ui;
}


