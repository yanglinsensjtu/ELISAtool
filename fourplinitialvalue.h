#ifndef FOURPLINITIALVALUE_H
#define FOURPLINITIALVALUE_H
#include <QVector>
#include <Eigen/Core>

class FourPLInitialValue
{
private:
    Eigen::Matrix<float, 2, 2> a;
    Eigen::Matrix<float, 2, 1> b;
    float initialA, initialB, initialC, initialD;
    QVector<float> variationY, variationX;
    QVector<float> readValue, dilutionDrugValue;

public:
    FourPLInitialValue();
    FourPLInitialValue(QVector<float> readValue, QVector<float> dilutionDrugValue);
    ~FourPLInitialValue();
    QVector<float> getReadValue() const;
    void setReadValue(const QVector<float> &value);
    QVector<float> getDilutionDrugValue() const;
    void setDilutionDrugValue(const QVector<float> &value);
    float getInitialA() const;
    void setInitialA(QVector<float> value);
    float getInitialD() const;
    void setInitialD(QVector<float> value);
    QVector<float> getVariationY() const;
    void setVariationY(const QVector<float> &value, float initialA, float initialB);
    QVector<float> getVariationX() const;
    void setVariationX(const QVector<float> &value);
    float getInitialB() const;
    void setInitialB(Eigen::Matrix<float, 2, 2> a, Eigen::Matrix<float, 2, 1> b);
    float getInitialC() const;
    void setInitialC(Eigen::Matrix<float, 2, 2> a, Eigen::Matrix<float, 2, 1> b, float iniB);
    Eigen::Matrix<float, 2, 2> getA() const;
    void setA(QVector<float> X);
    Eigen::Matrix<float, 2, 1> getB() const;
    void setB(QVector<float> X, QVector<float> Y);
};

#endif // FOURPLINITIALVALUE_H
