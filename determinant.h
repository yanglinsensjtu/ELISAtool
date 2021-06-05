#ifndef DETERMINANT_H
#define DETERMINANT_H
#include <qvector.h>

class Determinant
{

public:
    void Swap(int &a, int &b);
    void Perm(QVector<int> vec, QVector<QVector<int> > *vec_seq, int begin, int end);
    float calculate(QVector<QVector<float> > vec_Determinant, int n);
    bool Iseven(int num);
    bool PowerIsPosition(QVector<int> & vec);
    QVector<int> inivec(int n);

    Determinant();
    ~Determinant();

};

#endif // DETERMINANT_H
