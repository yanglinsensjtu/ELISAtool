#ifndef LEVENBERGMARQUARELT_H
#define LEVENBERGMARQUARELT_H
#include <Eigen/Dense>
#include <QVector>

using namespace Eigen;
class LevenbergMarquarelt
{
private:
    QVector<double> Yd, Xd;
    MatrixXd A_, g_, J_;
    int k = 0 , k_max = 100, v = 2;
    VectorXd P, Po_, Ep_, deltaP;
    double e1 = 1e-15, e2 = 1e-15,e3 = 1e-15, rho, mu, tao = 1e-3;
    bool stop;


public:


    LevenbergMarquarelt();
    ~LevenbergMarquarelt();
    VectorXd Solve();
    VectorXd LM();
    VectorXd Ep(QVector<double> Xd, QVector<double> Yd, double A, double B, double C, double D);
    double infinite_norm(MatrixXd g_);
    double two_norm(MatrixXd g_);
    MatrixXd A() const;
    void setA();
    MatrixXd J() const;
    void setJ(QVector<double> vec, double A, double B, double C, double D);
    VectorXd Po() const;
    void setPo(double A, double B, double C, double D);
    VectorXd Ep() const;
    void setEp(QVector<double> Xd, QVector<double> Yd, double A, double B, double C, double D);
    double getMu() const;
    void setMu();
    MatrixXd getG() const;
    void setG();
};

#endif // LEVENBERGMARQUARELT_H
