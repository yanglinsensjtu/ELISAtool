#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVector>
#include "Eigen/Core"
#include <iostream>




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    Determinant * D = new Determinant();
//    QVector<int> V = D->inivec(5);
//    QVector<QVector<int>> vec_seq;
//    D->Perm(V,&vec_seq,0,V.size()-1);
//    double** array = new double*[2];
//    for (int i = 0; i < 2; i++)
//    {
//        array[i] = new double[2];
//    }
//    array[0][0]=1.0129048;
//    array[0][1]=2.1384738185;
//    array[1][0]=1.13445;
//    array[1][1]=1.1394835;

//    QVector<QVector<double>> vec_determ;
//    QVector<double> vec1, vec2;
//    vec1.push_back(1.123);
//    vec1.push_back(12.34);
//    vec2.push_back(1.837);
//    vec2.push_back(2.3948);
//    vec_determ.push_back(vec1);
//    vec_determ.push_back(vec2);





//    qDebug()<<  vec_determ[0][0]<<D->calculate(vec_determ, 2);



//    for (int i = 0; i < 2; i++)
//    {
//        delete [] array[i];
//    }
//    delete [] array;

}

MainWindow::~MainWindow()
{
    delete ui;
}


