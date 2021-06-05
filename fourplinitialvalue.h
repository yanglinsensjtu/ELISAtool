#ifndef FOURPLINITIALVALUE_H
#define FOURPLINITIALVALUE_H
#include <QVector>

class FourPLInitialValue
{
private:
    float initialA, initialB, initialC, initialD;
    QVector<float> variationY, variationX;
    QVector<float> readValue, dilutionDrugValue;

public:
    FourPLInitialValue();
    ~FourPLInitialValue();
    QVector<float> getReadValue() const;
    void setReadValue(const QVector<float> &value);
    QVector<float> getDilutionDrugValue() const;
    void setDilutionDrugValue(const QVector<float> &value);
    float getInitialA() const;
    void setInitialA(QVector<float> value);
    float getInitialD() const;
    void setInitialD(QVector<float> value);
};

#endif // FOURPLINITIALVALUE_H
