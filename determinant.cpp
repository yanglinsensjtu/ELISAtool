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
    a = b;
    b = temp;
}
//生成初始数列


//计算全排列
void Determinant::Perm(QVector<int> vec, QVector<QVector<int>> *vec_seq, int begin, int end)
{
    if (begin == end)
    {
            vec_seq->push_back(vec);
    }
    else
    {
        for (int i = begin; i <= end; i++)
        {
            Swap(vec[begin], vec[i]);
            Perm(vec, vec_seq, begin + 1, end);
            Swap(vec[begin], vec[i]);
        }
    }

}
//初始化序列生成
QVector<int> Determinant::inivec(int n)
{
    QVector<int> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back(i);
    }
    return vec;
}
bool Determinant::Iseven(int num)
{
//用位运算来判断奇偶性
    return ((num & 1) == 0);

}

double Determinant::Value()
{



}


