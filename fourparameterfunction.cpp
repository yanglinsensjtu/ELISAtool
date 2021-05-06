#include "fourparameterfunction.h"
#include <math.h>
#include <QVector>

FourParameterFunction::FourParameterFunction()
{

}
//four pararmeter logitic function

QVector<double>  FourParameterFunction::Partialerivative(QVector<double> xVector,
                                                         double A,
                                                         double B,
                                                         double C,
                                                         double D)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        yVector[i] = D+(A-D)/(1+pow((xVector[i]/C),B));
    }
    return yVector;

}

QVector<double> FourParameterFunction::PartialerivativeA(QVector<double> xVector,
                                                         double B,
                                                         double C)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        1/(1+(x/C)^B)
        yVector[i] = 1/(1+pow((xVector[i]/C),B));
    }
    return yVector;

}

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
        yVector[i] = pow(xVector[i]/C, B)*(log(xVector[i]/C)*((D-A)/pow((1+pow(xVector[i]/C,B)),2)));
    }
    return yVector;

}

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
        yVector[i] = pow(xVector[i]/C, B)*((A-D)/(pow(1+pow(xVector[i]/C,B),2)))*(B/C);
    }
    return yVector;
}

QVector<double> FourParameterFunction::PartialerivativeD(QVector<double> xVector,
                                                         double B,
                                                         double C)
{
    QVector<double> yVector;
    for (int i = 0; i < xVector.size(); i++)
    {
        //        1-1/(1+(x/C)^B)
        yVector[i] = 1-1/(1+pow((xVector[i]/C), B));
    }
    return yVector;
}





