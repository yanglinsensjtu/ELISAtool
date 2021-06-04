#ifndef GROUP_H
#define GROUP_H
#include <QVector>
#include <Eigen/Core>

class Group
{
private:
    int row;
    int col;
    int rowCount;
    int colCount;
    double S_value;
    double D_value;
    QString name;
    QVector<double> Mean_value_Vec;
    //    保存所有数据
    Eigen::Matrix<double, 8, 12> Matrix_G;
public:
    Group(int r, int c, int rc, int cc);

    ~Group();

    double getS_value() const;
    void setS_value(double value);
    double getD_value() const;
    void setD_value(double value);
    int getRow() const;
    void setRow(int value);
    int getCol() const;
    void setCol(int value);
    int getRowCount() const;
    void setRowCount(int value);
    int getColCount() const;
    void setColCount(int value);
    Eigen::Matrix<double, 8, 12> getMatrix_G() const;
    void setMatrix_G(const Eigen::Matrix<double, 8, 12> &value);
    QString getName() const;
    void setName(const QString &value);
};

#endif // GROUP_H