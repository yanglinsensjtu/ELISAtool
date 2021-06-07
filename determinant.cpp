#include "determinant.h"
#include <iostream>
#include <QVector>
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

double Determinant::calculate(Eigen::Matrix<double, 2, 2> M)
{
    int n = 2;
    QVector<QVector<int>> vec_que;
    QVector<int> vec = inivec(n);
    QVector<int> vec_elem;
    //    最终结果初始化为0
    Perm(vec, &vec_que,0,vec.size()-1);
    double result = 0;
    //    依次从vec_que中取出行列式
    for (int i = 0; i < vec_que.size(); i++)
    {
        vec_elem = vec_que[i];
        //    mi即为前面(-1)的n次幂，最后结果为-1或者1
        int mi = PowerIsPosition(vec_elem) ? 1 : -1;
        float temp  = mi;
        //        row号初始化为0之后依次加1
        int row = 0;
        //        col号依次从vec_elem中取出
        for (int j = 0; j < (int)vec_elem.size(); j++)
        {
            int col = vec_elem[j];

//            temp *= vec_Determinant[row++][col];
            temp *= M(row++, col);
        }
        result += temp;

    }
    return result;

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
//增加判断逆序数的函数
bool Determinant::PowerIsPosition(QVector<int> &vec)
{
    //    count即为逆序数，初始化为0
    int count = 0;
    for (int i = 0; i < (int)vec.size(); i++)
    {
        for (int j = i + 1; j < (int)vec.size(); j++)
        {
            if (vec[i] > vec[j])
            {
                count += 1;
            }
        }
    }
    return (Iseven(count));
}

//float Determinant::calculate(QVector<QVector<float>> vec_Determinant, int n)
//{
//    QVector<QVector<int>> vec_que;
//    QVector<int> vec = inivec(n);
//    QVector<int> vec_elem;
//    //    最终结果初始化为0
//    Perm(vec, &vec_que,0,vec.size()-1);
//    float result = 0;
//    //    依次从vec_que中取出行列式
//    for (int i = 0; i < vec_que.size(); i++)
//    {
//        vec_elem = vec_que[i];
//        //    mi即为前面(-1)的n次幂，最后结果为-1或者1
//        int mi = PowerIsPosition(vec_elem) ? 1 : -1;
//        float temp  = mi;
//        //        row号初始化为0之后依次加1
//        int row = 0;
//        //        col号依次从vec_elem中取出
//        for (int j = 0; j < (int)vec_elem.size(); j++)
//        {
//            int col = vec_elem[j];

//            temp *= vec_Determinant[row++][col];
//        }
//        result += temp;

//    }
//    return result;

//}


