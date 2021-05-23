#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "determinant.h"
#include <QPoint>

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


private slots:
    void on_confirmStartCon_clicked();

    void on_confirmDilutionFold_clicked();
    void show_menu(const QPoint pos);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
