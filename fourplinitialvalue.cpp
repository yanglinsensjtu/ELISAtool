#include "fourplinitialvalue.h"
#include <cmath>
#include <algorithm>
#include <Eigen/Core>
#include "determinant.h"
using namespace std;
QVector<float> FourPLInitialValue::getReadValue() const
{
    return readValue;
}

void FourPLInitialValue::setReadValue(const QVector<float> &value)
{
    readValue = value;
}

QVector<float> FourPLInitialValue::getDilutionDrugValue() const
{
    return dilutionDrugValue;
}

void FourPLInitialValue::setDilutionDrugValue(const QVector<float> &value)
{
    dilutionDrugValue = value;
}

float FourPLInitialValue::getInitialA() const
{
    return initialA;
}
//从检测数据的均值中返回最小值作为A的初值
void FourPLInitialValue::setInitialA(QVector<float> value)
{
    initialA = *min_element(value.begin(),value.end());
}
float FourPLInitialValue::getInitialD() const
{
    return initialD;
}

//从检测数据的均值中返回最大值作为D的初值
void FourPLInitialValue::setInitialD(QVector<float> value)
{
    initialD = *max_element(value.begin(),value.end());
}

QVector<float> FourPLInitialValue::getVariationY() const
{
    return variationY;
}
//求线性变化后y的值
void FourPLInitialValue::setVariationY(const QVector<float> &value, float initialA, float initialD)
{
    QVector<float> tmp1;
    for(int i = 0; i <value.size(); i ++){
        tmp1.push_back(value.at(i)-initialD);
    }
    QVector<float> tmp2;
    for(int i = 0; i <value.size(); i ++){
        tmp2.push_back(initialA-value.at(i));
    }
    QVector<float> tmp3;
    for(int i = 0; i <value.size(); i ++){
        tmp3.push_back(log(tmp1.at(i)/tmp2.at(i)));
    }
    variationY = tmp3;
}



QVector<float> FourPLInitialValue::getVariationX() const
{
    return variationX;
}
//求线性变换后想x的值
void FourPLInitialValue::setVariationX(const QVector<float> &value)
{
    QVector<float> tmp;
    for(int i = 0 ; i < value.size(); i++)
    {
        tmp.push_back(log(value.at(i)));
    }
    variationX = tmp;
}

float FourPLInitialValue::getInitialB() const
{
    return initialB;
}

void FourPLInitialValue::setInitialB(Eigen::Matrix<float, 2, 2> a, Eigen::Matrix<float, 2, 1> b)
{
    Eigen::Matrix<float, 2, 2> DD1;
    DD1 = a;
    DD1(0,0)=b(0,0);
    DD1(0,1)=b(0,1);
    Determinant *Deter = new Determinant();
    float  tmp = -Deter->calculate(DD1)/Deter->calculate(a);
    initialB = tmp;
    delete Deter;
}

float FourPLInitialValue::getInitialC() const
{
    return initialC;
}

void FourPLInitialValue::setInitialC(Eigen::Matrix<float, 2, 2> a, Eigen::Matrix<float, 2, 1> b, float iniB)
{
    Eigen::Matrix<float, 2, 2> DD2;
    DD2 = a;
    DD2(1,0)=b(0,0);
    DD2(1,1)=b(0,1);
    Determinant *Deter = new Determinant();
    float  tmp = exp(Deter->calculate(DD2)/Deter->calculate(a)/iniB);

    initialC = tmp;
    delete Deter;
}

Eigen::Matrix<float, 2, 2> FourPLInitialValue::getA() const
{
    return a;
}

void FourPLInitialValue::setA(QVector<float> X)
{
    QVector<float> X2;
    for(int i = 0; i < X.size(); i++){
        X2.push_back(pow(X.at(i),2));
    }
    float sumX2 = 0.0, sumX = 0.0;
    for(int i = 0; i < X.size(); i++){
        sumX2 += X2.at(i);
        sumX += X.at(i);
    }
    Eigen::Matrix<float, 2, 2> tmp;
    tmp(0,0) = sumX;
    tmp(0,1) = X.size();
    tmp(1,0) = sumX2;
    tmp(1,1) = sumX;

    a = tmp;
}

Eigen::Matrix<float, 2, 1> FourPLInitialValue::getB() const
{
    return b;
}

void FourPLInitialValue::setB(QVector<float> X, QVector<float> Y)
{
    QVector<float> XY;
    for(int i = 0; i < X.size(); i ++){
        XY.push_back(X.at(i)*Y.at(i));
    }
    float sumY = 0.0, sumXY = 0.0;
    for(int i = 0; i < Y.size(); i ++){
        sumY += Y.at(i);
        sumXY += XY.at(i);
    }
    Eigen::Matrix<float, 2, 1> tmp;
    tmp(0, 0) = -sumY;
    tmp(0 ,1) = sumXY;
    b = tmp;
}

FourPLInitialValue::FourPLInitialValue()
{
    
}
