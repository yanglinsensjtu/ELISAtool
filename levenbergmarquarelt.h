#ifndef LEVENBERGMARQUARELT_H
#define LEVENBERGMARQUARELT_H
#include <Eigen/Dense>
#include <QVector>

using namespace Eigen;
class LevenbergMarquarelt
{
private:
    QVector<double> Yd;
    QVector<double> Xd;
    MatrixXd A_;
    VectorXd g_;
    MatrixXd J_;
    int k = 0 ;
    int k_max = 100;
    int v = 2;
    Vector4d P;
    Vector4d Po_;
    VectorXd Ep_;
    Vector4d deltaP;
    double e1 = 1e-15;
    double e2 = 1e-15;
    double e3 = 1e-15;
    double rho;
    double mu;
    double tao = 1e-3;
    bool stop;


public:


    LevenbergMarquarelt();
    LevenbergMarquarelt(QVector<double> X, QVector<double> Y, double A, double B,double C, double D);
    ~LevenbergMarquarelt();
    VectorXd Solve();
    VectorXd LM();
    VectorXd Ep_update(QVector<double> Xd, QVector<double> Yd, double A, double B, double C, double D);

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
    VectorXd getG() const;
    void setG();
};

#endif // LEVENBERGMARQUARELT_H
