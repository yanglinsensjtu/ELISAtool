#include "determinant.h"
#include <iostream>
#include <qvector.h>
#include <QDebug>
using namespace std;
Determinant::Determinant()
{

}

//数值交换
void Determinant::Swap(int &a, int &b)
{
    int temp = a;
    a = b;;
    b = temp;
}
//生成初始数列


//计算全排列
void Determinant::Perm(QVector<int> vec, int begin, int end)
{
    if (begin == end)
    {
        for (int i = 0; i <= end; i++)
        {
            qDebug() << vec[i];
        }

    }
    else
    {
        for (int i = begin; i <= end; i++)
        {
            Swap(vec[begin], vec[i]);
            Perm(vec, begin + 1, end);
            Swap(vec[begin], vec[i]);
        }
    }
}

QVector<int> Determinant::inivec(int n)
{
    QVector<int> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back(i);


    }
    return vec;
}

double Determinant::Value()
{



}


