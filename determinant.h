#ifndef DETERMINANT_H
#define DETERMINANT_H
#include <QVector>
#include <Eigen/Dense>

class Determinant
{

public:
    void Swap(int &a, int &b);
    void Perm(QVector<int> vec, QVector<QVector<int> > *vec_seq, int begin, int end);
    double calculate(Eigen::Matrix<double, 2, 2> M);
    bool Iseven(int num);
    bool PowerIsPosition(QVector<int> & vec);
    QVector<int> inivec(int n);

    Determinant();
    ~Determinant();

};

#endif // DETERMINANT_H
