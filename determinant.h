#ifndef DETERMINANT_H
#define DETERMINANT_H
#include <qvector.h>

class Determinant
{

public:
    void Swap(int &a, int &b);
    void Perm(QVector<int> vec, QVector<QVector<int> > *vec_seq, int begin, int end);
    double Value();
    bool Iseven(int num);
    QVector<int> inivec(int n);

    Determinant();
    ~Determinant();

};

#endif // DETERMINANT_H
