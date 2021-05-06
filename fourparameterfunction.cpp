#include "fourparameterfunction.h"
#include <math.h>


double FourParameterFunction::Partialerivative(double array, double A, double B, double C, double D)
{
        return D+(A-D)/(1+pow((array/C),B));

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
