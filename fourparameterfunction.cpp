#include "fourparameterfunction.h"
#include <math.h>
#include <QVector>


QVector<double>  FourParameterFunction::Partialerivative(QVector<double> xVector,
                                                         QVector<double> yVector,
                                                         double A,
                                                         double B,
                                                         double C,
                                                         double D)
{
    for (int i = 0; i < xVector.size(); i++)
    {
        yVector[i] = D+(A-D)/(1+pow((xVector[i]/C),B));
    }
        return yVector;

}

double FourParameterFunction::PartialerivativeA()
{

}

double FourParameterFunction::PartialerivativeB()
{

}

double FourParameterFunction::PartialerivativeC()
{

}

double FourParameterFunction::PartialerivativeD()
{

}

FourParameterFunction::FourParameterFunction()
{

}
