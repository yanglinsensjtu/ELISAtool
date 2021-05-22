#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "determinant.h"

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

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
