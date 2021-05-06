#ifndef FOURPARAMETERFUNCTION_H
#define FOURPARAMETERFUNCTION_H
#include <QVector>

class FourParameterFunction
{
public:

    QVector<double>  Partialerivative(QVector<double> xVector,
                                      QVector<double> yVector,
                                      double A,
                                      double B,
                                      double C,
                                      double D);
    double PartialerivativeA();
    double PartialerivativeB();
    double PartialerivativeC();
    double PartialerivativeD();

    FourParameterFunction();
    ~FourParameterFunction();
};

#endif // FOURPARAMETERFUNCTION_H
