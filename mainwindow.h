#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "determinant.h"
#include <QPoint>
#include <QMouseEvent>
#include <Eigen/Dense>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Determinant *D = new Determinant();



private slots:
    void on_confirmStartCon_clicked();
    void on_confirmDilutionFold_clicked();
    void show_menu();
    void show_list_menu();
    void copy();
    void cut();
    void paste();
    void clear();
    void addgroup();
    void rename();
    void on_dataFit_btn_clicked();
    void on_pushButton_2_clicked();

private:
    //    保存分组的个数
    int group_count = 0;
//    保存分组后的tablewidget
    QVector<QTableWidget*> qtw;
    //    保存所有数据
    Eigen::Matrix<double, 8, 12> Matrix_x;
    //    保存分组数据的矩阵坐标
    int r_g, c_g, rc_g, cc_g;
    //    起始浓度
    float S_Value_d = 2000, D_Value_d = 4;

    //    Group *group1 = new Group(0,0,0,0);
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
