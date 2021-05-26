#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVector>
#include "Eigen/Core"
#include <iostream>
#include <QRegExp>
#include <QDoubleValidator>
#include <QClipboard>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget_excel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget_excel,SIGNAL(customContextMenuRequested(QPoint)), this , SLOT(show_menu()));


//    connect(ui-> confirmStartCon, SIGNAL(clicked()), this, SLOT(on_confirmStartCon_clicked()) );

//    QString startConcentration = ui->startConcentration->setText();
//    qDebug() << startConcentration;
//    Determinant * D = new Determinant();
//    QVector<int> V = D->inivec(5);
//    QVector<QVector<int>> vec_seq;
//    D->Perm(V,&vec_seq,0,V.size()-1);
//    double** array = new double*[2];
//    for (int i = 0; i < 2; i++)
//    {
//        array[i] = new double[2];
//    }
//    array[0][0]=1.0129048;
//    array[0][1]=2.1384738185;
//    array[1][0]=1.13445;
//    array[1][1]=1.1394835;

//    QVector<QVector<double>> vec_determ;
//    QVector<double> vec1, vec2;
//    vec1.push_back(1.123);
//    vec1.push_back(12.34);
//    vec2.push_back(1.837);
//    vec2.push_back(2.3948);
//    vec_determ.push_back(vec1);
//    vec_determ.push_back(vec2);

//    Eigen::Matrix3d m,m1,m2;
//    Eigen::Matrix<double, 3, 6> m4;
//    m << 1,2, 3,4,5,6,7,8,9;
//    m1 << 1,2, 3,4,5,6,7,8,9;
//    m4 << m, m1;




//    std::cout << m4 << std::endl;



//    qDebug()<<  vec_determ[0][0]<<D->calculate(vec_determ, 2);



//    for (int i = 0; i < 2; i++)
//    {
//        delete [] array[i];
//    }
//    delete [] array;
//    设置数字输入限制
    QDoubleValidator *aQDoubleValidator = new QDoubleValidator(50,50,5,this);
    ui->startConcentration->setValidator(aQDoubleValidator);
    ui->dilutionValue->setValidator(aQDoubleValidator);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_confirmStartCon_clicked()
{
    QString S_Value = ui->startConcentration->text();
    ui->display_S_value->setText(S_Value);
    qDebug()<< S_Value.toDouble();

}

void MainWindow::on_confirmDilutionFold_clicked()
{
    QString D_Value = ui->dilutionValue->text();
    ui->display_D_value->setText(D_Value);
    qDebug()<<D_Value.toDouble();
}
//自定义tablewidget右键菜单 复制 黏贴 剪切
void MainWindow::show_menu()
{
        QMenu *menu = new QMenu(ui->tableWidget_excel);
        QAction *pnew = new QAction("Copy", ui->tableWidget_excel);
        connect(pnew, SIGNAL(triggered()),this, SLOT(copy()));
        QAction *pnew2 = new QAction("Paste", ui->tableWidget_excel);
        connect(pnew2, SIGNAL(triggered()),this, SLOT(paste()));
        QAction *pnew3 = new QAction("Cut", ui->tableWidget_excel);
        connect(pnew3, SIGNAL(triggered()),this, SLOT(cut()));
        QAction *pnew4 = new QAction("Clear", ui->tableWidget_excel);
        connect(pnew4, SIGNAL(triggered()),this, SLOT(clear()));
        QAction *pnew5 = new QAction("Add Group",ui->tableWidget_excel);
        connect(pnew5, SIGNAL(triggered()), this, SLOT(addgroup()));
        menu->addAction(pnew);
        menu->addAction(pnew2);
        menu->addAction(pnew3);
        menu->addAction(pnew4);
        menu->addSeparator();
        menu->addAction(pnew5);
        menu->move(cursor().pos());
        menu->show();
//        int x = pos.x();
//        int y = pos.y();
//        QModelIndex index = ui->tableWidget_excel->indexAt(QPoint(x,y));
//        int row = index.row(); //获取QTableWidget列表点击的行数
//        int col = index.column();
//        qDebug()<< row << col;
//        QClipboard *qclipboard = QGuiApplication::clipboard();
//        QString qclipboard_text = qclipboard->text();
//        paste(row, col, qclipboard_text);
//        connect(pnew2, &pnew2->trigger(), this, &MainWindow::paste());
//        return pos;

}
//tablewidget右击菜单复制函数实现
void MainWindow::copy()
{
    QList<QTableWidgetSelectionRange> a = ui->tableWidget_excel->selectedRanges();

    qDebug()<<"调用copy"<<a.at(0).topRow();
}
//tablewidget右击菜单剪切函数实现
void MainWindow::cut()
{
    qDebug()<<"调用cut";
}
//tablewidget右击菜单黏贴函数实现
void MainWindow::paste()
{
    QClipboard *qclipboard = QGuiApplication::clipboard();
    QString qclipboard_text = qclipboard->text();
    QStringList q_str_list = qclipboard_text.split(QRegExp("\\r\\n|\\t"));
//    确定复制了多少行
    int count = qclipboard_text.count(QRegExp("\\r\\n"));

//    选取选中的行列
    QList<QTableWidgetSelectionRange> SelectedRange = ui->tableWidget_excel->selectedRanges();
//    确定起始点的行位置和起始点的列位置
    int r = SelectedRange.at(0).topRow();
    int c = SelectedRange.at(0).leftColumn();
//将复制的数据黏贴在选中的起始位置上
    for (int i = 0; i < count+1; i++) {
        for (int j = 0;j< q_str_list.size()/(count+1);j++) {
            ui->tableWidget_excel->setItem(i+r,j+c,new QTableWidgetItem(q_str_list.at(q_str_list.size()/(count+1)*i+j)));            
        }
    }
}

void MainWindow::clear()
{
    ui->tableWidget_excel->clear();
}
//增加数据分组
void MainWindow::addgroup()
{
    //    选取选中的行列
    QList<QTableWidgetSelectionRange> SelectedRange = ui->tableWidget_excel->selectedRanges();
    int r = SelectedRange.at(0).topRow();
    int c = SelectedRange.at(0).leftColumn();
    int rc = SelectedRange.at(0).rowCount();
    int cc = SelectedRange.at(0).columnCount();
    for (int i = 0;i < rc; i++) {
        for (int j = 0;j < cc; j++) {
            ui->tableWidget_excel->item(i+r,j+c)->setBackgroundColor("red");
        }
    }
    ui->listWidget->addItem("分组1");
}







