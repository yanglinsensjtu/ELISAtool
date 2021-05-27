#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "determinant.h"
#include <QPoint>
#include <QMouseEvent>
#include <Eigen/Core>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
//    Determinant *D = new Determinant();
    Eigen::Matrix<double, 8, 12> Matrix_x;
    int r_g, c_g, rc_g, cc_g;


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




private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
