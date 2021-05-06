#ifndef FOURPARAMETERFUNCTION_H
#define FOURPARAMETERFUNCTION_H


class FourParameterFunction
{
public:

    double Partialerivative(double array, double A, double B, double C, double D);
    double PartialerivativeA();
    double PartialerivativeB();
    double PartialerivativeC();
    double PartialerivativeD();

    FourParameterFunction();
    ~FourParameterFunction();
};

#endif // FOURPARAMETERFUNCTION_H
