#ifndef FOURPARAMETERFUNCTION_H
#define FOURPARAMETERFUNCTION_H
#include <QVector>
#include <Eigen/Core>

class FourParameterFunction
{
public:

    QVector<double> Partialerivative(QVector<double> xVector,
                                      double A,
                                      double B,
                                      double C,
                                      double D);
    QVector<double> PartialerivativeA(QVector<double> xVector,
                                      double B,
                                      double C);
    QVector<double> PartialerivativeB(QVector<double> xVector,
                                      double A,
                                      double B,
                                      double C,
                                      double D);
    QVector<double> PartialerivativeC(QVector<double> xVector,
                                      double A,
                                      double B,
                                      double C,
                                      double D);
    QVector<double> PartialerivativeD(QVector<double> xVector,
                                      double B,
                                      double C);
    Eigen::MatrixX4d JocabiMatrix(QVector<double> xVecotr,
                                 double A,
                                 double B,
                                 double C,
                                 double D);

    FourParameterFunction();
    ~FourParameterFunction();
};

#endif // FOURPARAMETERFUNCTION_H
