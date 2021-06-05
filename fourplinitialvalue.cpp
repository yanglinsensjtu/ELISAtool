#include "fourplinitialvalue.h"
#include <cmath>
#include <algorithm>
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

void FourPLInitialValue::setVariationX(const QVector<float> &value)
{
    variationX = value;
}

FourPLInitialValue::FourPLInitialValue()
{
    
}
