#include "fourparameterfunction.h"
#include <math.h>
#include <QVector>
#include <QDebug>

FourParameterFunction::FourParameterFunction()
{

}
//four pararmeter logitic function

QVector<double>  FourParameterFunction::FourPLFunction(QVector<double> xVector,
                                                         double A,
                                                         double B,
                                                         double C,
                                                         double D)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
//        D+(A-D)/(1+(x/C)^B)
        yVector.push_back(D+(A-D)/(1+pow((xVector.at(i)/C),B)));
    }
    return yVector;

}

//参数A的偏导数
QVector<double> FourParameterFunction::PartialerivativeA(QVector<double> xVector,
                                                         double B,
                                                         double C)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        1/(1+(x/C)^B)
        yVector.push_back(1/(1+pow((xVector.at(i)/C),B)));
    }
    return yVector;

}
//参数B的偏导数
QVector<double> FourParameterFunction::PartialerivativeB(QVector<double> xVector,
                                                         double A,
                                                         double B,
                                                         double C,
                                                         double D)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        ((x/C)^B)*(log(x/C))*((D-A)/((1+(x/C)^B)^2))
        yVector.push_back(pow(xVector.at(i)/C, B)*(log(xVector.at(i)/C)*((D-A)/pow((1+pow(xVector.at(i)/C,B)),2))));
    }
    return yVector;

}
//参数C的偏导数
QVector<double> FourParameterFunction::PartialerivativeC(QVector<double> xVector,
                                                         double A,
                                                         double B,
                                                         double C,
                                                         double D)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        ((x/C)^B)*((A-D)/((1+(x/C)^B)^2))*(B/C)
        yVector.push_back(pow(xVector.at(i)/C, B)*((A-D)/(pow(1+pow(xVector.at(i)/C,B),2)))*(B/C));
    }
    return yVector;
}
//参数D的偏导数
QVector<double> FourParameterFunction::PartialerivativeD(QVector<double> xVector,
                                                         double B,
                                                         double C)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        1-1/(1+(x/C)^B)
        yVector.push_back(1-1/(1+pow((xVector.at(i)/C), B)));
    }
    return yVector;
}

//四参数方程的雅克比矩阵
Eigen::MatrixXd FourParameterFunction::JocabiMatrix(QVector<double> xVecotr, double A, double B, double C, double D)
{
    QVector<double> PA = PartialerivativeA(xVecotr,B,C);
    QVector<double> PB = PartialerivativeB(xVecotr,A,B,C,D);
    QVector<double> PC = PartialerivativeC(xVecotr,A,B,C,D);
    QVector<double> PD = PartialerivativeD(xVecotr,B,C);
    Eigen::MatrixX4d tmp;
    tmp.resize(xVecotr.size(),4);
    for(int i = 0; i < xVecotr.size(); i++){
        tmp(i,0) = PA.at(i);
        tmp(i,1) = PB.at(i);
        tmp(i,2) = PC.at(i);
        tmp(i,3) = PD.at(i);

    }
    return tmp;
}





