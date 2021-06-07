#include "fourplinitialvalue.h"
#include <cmath>
#include <algorithm>
#include <Eigen/Core>
#include "determinant.h"
#include <QDebug>
#include <stdio.h>
#include <iostream>
using namespace std;
QVector<double> FourPLInitialValue::getReadValue() const
{
    return readValue;
}

void FourPLInitialValue::setReadValue(const QVector<double> &value)
{
    readValue = value;
}

QVector<double> FourPLInitialValue::getDilutionDrugValue() const
{
    return dilutionDrugValue;
}

void FourPLInitialValue::setDilutionDrugValue(const QVector<double> &value)
{
    dilutionDrugValue = value;
}

double FourPLInitialValue::getInitialA() const
{
    return initialA;
}
//从检测数据的均值中返回最小值作为A的初值
void FourPLInitialValue::setInitialA(QVector<double> value)
{
    initialA = *min_element(value.begin(),value.end()) - 0.01;
}
double FourPLInitialValue::getInitialD() const
{
    return initialD;
}

//从检测数据的均值中返回最大值作为D的初值
void FourPLInitialValue::setInitialD(QVector<double> value)
{
    initialD = *max_element(value.begin(),value.end()) + 0.01;
}

QVector<double> FourPLInitialValue::getVariationY() const
{
    return variationY;
}
//求线性变化后y的值
void FourPLInitialValue::setVariationY(const QVector<double> &value, double initialA, double initialD)
{
    QVector<double> tmp1;
    for(int i = 0; i <value.size(); i ++){
        tmp1.push_back(value.at(i)-initialD);
    }
    QVector<double> tmp2;
    for(int i = 0; i <value.size(); i ++){
        tmp2.push_back(initialA-value.at(i));
    }
    QVector<double> tmp3;
    for(int i = 0; i <value.size(); i ++){
        tmp3.push_back(log(tmp1.at(i)/tmp2.at(i)));
    }
    variationY = tmp3;
}



QVector<double> FourPLInitialValue::getVariationX() const
{
    return variationX;
}
//求线性变换后想x的值
void FourPLInitialValue::setVariationX(const QVector<double> &value)
{
    QVector<double> tmp;
    for(int i = 0 ; i < value.size(); i++)
    {
        tmp.push_back(log(value.at(i)));
    }
    variationX = tmp;
}

double FourPLInitialValue::getInitialB() const
{
    return initialB;
}

void FourPLInitialValue::setInitialB(Eigen::Matrix<double, 2, 2> aDeter, Eigen::Matrix<double, 2, 1> bDeter)
{
    Eigen::Matrix<double, 2, 2> DD1;
    DD1 = aDeter;
    DD1(0,0)=bDeter(0,0);
    DD1(0,1)=bDeter(1,0);
    Determinant *Deter = new Determinant();
    double  tmp = -Deter->calculate(DD1)/Deter->calculate(a);
    initialB = tmp;

}

double FourPLInitialValue::getInitialC() const
{
    return initialC;
}

void FourPLInitialValue::setInitialC(Eigen::Matrix<double, 2, 2> a, Eigen::Matrix<double, 2, 1> b, double iniB)
{
    Eigen::Matrix<double, 2, 2> DD2;
    DD2 = a;
    DD2(1,0)=b(0,0);
    DD2(1,1)=b(1,0);
    Determinant *Deter = new Determinant();
    double  tmp = exp(Deter->calculate(DD2)/Deter->calculate(a)/iniB);

    initialC = tmp;

}

Eigen::Matrix<double, 2, 2> FourPLInitialValue::getA() const
{
    return a;
}

void FourPLInitialValue::setA(QVector<double> X)
{
    QVector<double> X2;
    for(int i = 0; i < X.size(); i++){
        X2.push_back(pow(X.at(i),2));
    }
    double sumX2 = 0.0, sumX = 0.0;
    for(int i = 0; i < X.size(); i++){
        sumX2 += X2.at(i);
        sumX += X.at(i);
    }
    Eigen::Matrix<double, 2, 2> tmp;
    tmp(0,0) = sumX;
    tmp(0,1) = X.size();
    tmp(1,0) = sumX2;
    tmp(1,1) = sumX;
    this->a = tmp;
}

Eigen::Matrix<double, 2, 1> FourPLInitialValue::getB() const
{
    return b;
}

void FourPLInitialValue::setB(QVector<double> X, QVector<double> Y)
{
    QVector<double> XY;
    for(int i = 0; i < X.size(); i ++){
        XY.push_back(X.at(i)*Y.at(i));
    }
    double sumY = 0.0, sumXY = 0.0;
    for(int i = 0; i < Y.size(); i ++){
        sumY += Y.at(i);
        sumXY += XY.at(i);
    }
    Eigen::Matrix<double, 2, 1> tmp;
    tmp(0, 0) = -sumY;
    tmp(1 ,0) = sumXY;
    this->b = tmp;
}

QVector<double> FourPLInitialValue::getInitialValue() const
{
    return initialValue;
}

void FourPLInitialValue::setInitialValue(const double &A, const double &B, const double &C, const double &D)
{
    QVector<double> value;
    value.push_back(A);
    value.push_back(B);
    value.push_back(C);
    value.push_back(D);
    initialValue = value;
}

FourPLInitialValue::FourPLInitialValue()
{
    
}

FourPLInitialValue::FourPLInitialValue(const QVector<double> readValue, const QVector<double> dilutionDrugValue)
{
    this->readValue = readValue;
    this->dilutionDrugValue = dilutionDrugValue;
    this->setInitialA(readValue);
    this->setInitialD(readValue);
    this->setVariationX(dilutionDrugValue);
    this->setVariationY(readValue,this->getInitialA(),this->getInitialD());
    this->setA(this->getVariationX());
    this->setB(this->getVariationX(),this->getVariationY());
    this->setInitialB(this->getA(),this->getB());
    this->setInitialC(this->getA(),this->getB(),this->getInitialB());
    this->setInitialValue(this->getInitialA(),this->getInitialB(),this->getInitialC(),this->getInitialD());
}
