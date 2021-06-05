#include "fourparameterfunction.h"
#include <math.h>
#include <QVector>

FourParameterFunction::FourParameterFunction()
{

}
//four pararmeter logitic function

QVector<float>  FourParameterFunction::Partialerivative(QVector<float> xVector,
                                                         float A,
                                                         float B,
                                                         float C,
                                                         float D)
{
    QVector<float> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        yVector[i] = D+(A-D)/(1+pow((xVector[i]/C),B));
    }
    return yVector;

}

//参数A的偏导数
QVector<float> FourParameterFunction::PartialerivativeA(QVector<float> xVector,
                                                         float B,
                                                         float C)
{
    QVector<float> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        1/(1+(x/C)^B)
        yVector[i] = 1/(1+pow((xVector[i]/C),B));
    }
    return yVector;

}
//参数B的偏导数
QVector<float> FourParameterFunction::PartialerivativeB(QVector<float> xVector,
                                                         float A,
                                                         float B,
                                                         float C,
                                                         float D)
{
    QVector<float> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        ((x/C)^B)*(log(x/C))*((D-A)/((1+(x/C)^B)^2))
        yVector[i] = pow(xVector[i]/C, B)*(log(xVector[i]/C)*((D-A)/pow((1+pow(xVector[i]/C,B)),2)));
    }
    return yVector;

}
//参数C的偏导数
QVector<float> FourParameterFunction::PartialerivativeC(QVector<float> xVector,
                                                         float A,
                                                         float B,
                                                         float C,
                                                         float D)
{
    QVector<float> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        ((x/C)^B)*((A-D)/((1+(x/C)^B)^2))*(B/C)
        yVector[i] = pow(xVector[i]/C, B)*((A-D)/(pow(1+pow(xVector[i]/C,B),2)))*(B/C);
    }
    return yVector;
}
//参数D的偏导数
QVector<float> FourParameterFunction::PartialerivativeD(QVector<float> xVector,
                                                         float B,
                                                         float C)
{
    QVector<float> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        1-1/(1+(x/C)^B)
        yVector[i] = 1-1/(1+pow((xVector[i]/C), B));
    }
    return yVector;
}
//四参数方程的雅克比矩阵
QVector<float> FourParameterFunction::JocabiMatrix(QVector<float> xVecotr, float A, float B, float C, float D)
{

}





