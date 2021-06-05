#ifndef FOURPARAMETERFUNCTION_H
#define FOURPARAMETERFUNCTION_H
#include <QVector>

class FourParameterFunction
{
public:

    QVector<float>  Partialerivative(QVector<float> xVector,
                                      float A,
                                      float B,
                                      float C,
                                      float D);
    QVector<float> PartialerivativeA(QVector<float> xVector,
                                      float B,
                                      float C);
    QVector<float> PartialerivativeB(QVector<float> xVector,
                                      float A,
                                      float B,
                                      float C,
                                      float D);
    QVector<float> PartialerivativeC(QVector<float> xVector,
                                      float A,
                                      float B,
                                      float C,
                                      float D);
    QVector<float> PartialerivativeD(QVector<float> xVector,
                                      float B,
                                      float C);
    QVector<float> JocabiMatrix(QVector<float> xVecotr,
                                 float A,
                                 float B,
                                 float C,
                                 float D);

    FourParameterFunction();
    ~FourParameterFunction();
};

#endif // FOURPARAMETERFUNCTION_H
