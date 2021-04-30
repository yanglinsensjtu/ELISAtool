#ifndef DETERMINANT_H
#define DETERMINANT_H
#include <qvector.h>

class Determinant
{

public:
    void Swap(int &a, int &b);
    void Perm(int list[], int begin, int end);
    double Value();
    QVector<int> inivec(int n);

    Determinant();
    ~Determinant();

};

#endif // DETERMINANT_H
