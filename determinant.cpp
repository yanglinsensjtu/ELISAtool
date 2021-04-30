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
void Determinant::Perm(int list[], int begin, int end)
{
    if (begin == end)
    {
        for (int i = 0; i <= end; i++)
        {
            cout << list[i];
        }
        cout << endl;
    }
    else
    {
        for (int i = begin; i <= end; i++)
        {
            Swap(list[begin], list[i]);
            Perm(list, begin + 1, end);
            Swap(list[begin], list[i]);
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


