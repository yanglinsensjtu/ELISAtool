#ifndef LMMETHOD_H
#define LMMETHOD_H
#include <Eigen/Dense>
#include <QVector>
using namespace Eigen;

class LMmethod
{
public:
    LMmethod();
    VectorXd LM(QVector<double> X,
                QVector<double> Y,
                double A,
                double B,
                double C,
                double D);
    VectorXd Ep(QVector<double> Xd,
                QVector<double> Yd,
                double A,
                double B,
                double C,
                double D);
    double infinite_norm(MatrixXd g_);
    double two_norm(MatrixXd g_);
    VectorXd Solve(MatrixXd A, MatrixXd g, double mu);
    double setMu(MatrixXd A, double tao);
    ~LMmethod();
};

#endif // LMMETHOD_H
