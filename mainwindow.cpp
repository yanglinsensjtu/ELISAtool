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
    int** array = new int*[2];
    for (int i = 0; i < 2; i++)
    {
        array[i] = new int[2];
    }
    array[0][0] = 2;
    array[0][1] = -4;

    array[1][0] = 1;
    array[1][1] = -5;

    qDebug()<< vec_seq[1]<< vec_seq.size() << D->Iseven(2)<<D->PowerIsPosition(vec_seq[1])<< D->calculate(array,2) << *array;

}

MainWindow::~MainWindow()
{
    delete ui;
}


