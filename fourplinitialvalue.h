#ifndef FOURPLINITIALVALUE_H
#define FOURPLINITIALVALUE_H
#include <QVector>
#include <Eigen/Dense>

class FourPLInitialValue
{
private:
    Eigen::Matrix<double, 2, 2> a;
    Eigen::Matrix<double, 2, 1> b;
    double initialA, initialB, initialC, initialD;
    double Bm, Cm;
    QVector<double> variationY, variationX;
    QVector<double> readValue, dilutionDrugValue;
    QVector<double> initialValue;

public:
    FourPLInitialValue();
    FourPLInitialValue(const QVector<double> readValue, const QVector<double> dilutionDrugValue);
    ~FourPLInitialValue();

    QVector<double> getReadValue() const;
    void setReadValue(const QVector<double> &value);

    QVector<double> getDilutionDrugValue() const;
    void setDilutionDrugValue(const QVector<double> &value);

    double getInitialA() const;
    void setInitialA(QVector<double> value);

    double getInitialD() const;
    void setInitialD(QVector<double> value);

    QVector<double> getVariationY() const;
    void setVariationY(const QVector<double> &value, double initialA, double initialB);

    QVector<double> getVariationX() const;
    void setVariationX(const QVector<double> &value);

    double getInitialB() const;
    void setInitialB(Eigen::Matrix<double, 2, 2> aDeter, Eigen::Matrix<double, 2, 1> bDeter);

    double getInitialC() const;
    void setInitialC(Eigen::Matrix<double, 2, 2> a, Eigen::Matrix<double, 2, 1> b, double iniB);

    Eigen::Matrix<double, 2, 2> getA() const;
    void setA(QVector<double> X);

    Eigen::Matrix<double, 2, 1> getB() const;
    void setB(QVector<double> X, QVector<double> Y);

    QVector<double> getInitialValue() const;
    void setInitialValue(const double &A, const double &B,const double &C,const double &D);
};

#endif // FOURPLINITIALVALUE_H
