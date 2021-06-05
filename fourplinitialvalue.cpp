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
//从检测数据的均值中返回最大值作为D的初值
float FourPLInitialValue::getInitialD() const
{
    return initialD;
}

void FourPLInitialValue::setInitialD(QVector<float> value)
{
    initialD = *max_element(value.begin(),value.end());
}

FourPLInitialValue::FourPLInitialValue()
{
    
}
