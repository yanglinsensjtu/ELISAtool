#include "group.h"

double Group::getS_value() const
{
    return S_value;
}

void Group::setS_value(double value)
{
    S_value = value;
}

double Group::getD_value() const
{
    return D_value;
}

void Group::setD_value(double value)
{
    D_value = value;
}

int Group::getRow() const
{
    return row;
}

void Group::setRow(int value)
{
    row = value;
}

int Group::getCol() const
{
    return col;
}

void Group::setCol(int value)
{
    col = value;
}

int Group::getRowCount() const
{
    return rowCount;
}

void Group::setRowCount(int value)
{
    rowCount = value;
}

int Group::getColCount() const
{
    return colCount;
}

void Group::setColCount(int value)
{
    colCount = value;
}

Eigen::Matrix<double, 8, 12> Group::getMatrix_G() const
{
    return Matrix_G;
}

void Group::setMatrix_G(const Eigen::Matrix<double, 8, 12> &value)
{
    Matrix_G = value;
}

QString Group::getName() const
{
    return name;
}

void Group::setName(const QString &value)
{
    name = value;
}

Group::Group(int r, int c, int rc, int cc)
{
    this->row = r;
    this->col = c;
    this->rowCount = rc;
    this->colCount = cc;
}
