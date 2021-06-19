#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
using namespace QtCharts;
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QVector>
#include <Eigen/Dense>
#include <iostream>
#include <QRegExp>
#include <QDoubleValidator>
#include <QClipboard>
#include <QColorDialog>
#include <QInputDialog>
#include <stdio.h>
#include <math.h>
#include <fourplinitialvalue.h>
#include <fourparameterfunction.h>
#include <algorithm>
#include <levenbergmarquarelt.h>
#include <lmmethod.h>
#include <QString>


using namespace Eigen;
using namespace std;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    增加tableWidget的总体右击菜单
    ui->tableWidget_excel->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableWidget_excel,SIGNAL(customContextMenuRequested(QPoint)), this , SLOT(show_menu()));
    //    增加listwidget的右击菜单
    ui->listWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget,SIGNAL(customContextMenuRequested(QPoint)), this , SLOT(show_list_menu()));



    //    设置数字输入限制
    QDoubleValidator *aQDoubleValidator = new QDoubleValidator(50,50,5,this);
    ui->startConcentration->setValidator(aQDoubleValidator);
    ui->dilutionValue->setValidator(aQDoubleValidator);
    //    Eigen::Matrix<float, 2, 2> M;
    //    M(0,0) = 1;
    //    M(0,1) = 2;
    //    M(1,0) = 3;
    //    M(1,1) = 4;

    //    qDebug() << D->calculate(M);
    //        QVector<double> X {2000,
    //                           500,
    //                           125,
    //                           31.25,
    //                           7.813,
    //                           1.953,
    //                           0.488,
    //                           0.122,
    //                           0.031,
    //                           0.008};
    //        QVector<double> Y {
    //            238760.776,
    //            238685.567,
    //            240710.229,
    //            223192.552,
    //            128388.818,
    //            26587.340,
    //            4961.271,
    //            3322.640,
    //            3338.803,
    //            3213.232};
    //        qDebug()<<X;
    //        qDebug()<<Y;
    //       double A =  3.181429e+03;
    //       double B =  1.501060e+00;
    //       double C =  1.658991e+00;
    //       double D =  2.373467e+05;
    //           LMmethod *LM = new LMmethod();
    //           cout << LM->LM(X,
    //                          Y,
    //                          A,
    //                          B,
    //                          C,
    //                          D);
    //       VectorXd Xm;
    //       Xm.resize(X.size(),1);

    //       for (int i = 0;i<X.size();i++) {
    //           Xm(i,0) = X.at(i);

    //       }
    //       cout << "LM->two_norm(Xm)" << endl;
    //       cout << LM->infinite_norm(Xm) << endl;

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_confirmStartCon_clicked()
{
    QString S_Value = ui->startConcentration->text();
    ui->display_S_value->setText(S_Value);
    S_Value_d =  S_Value.toDouble();
}

void MainWindow::on_confirmDilutionFold_clicked()
{
    QString D_Value = ui->dilutionValue->text();
    ui->display_D_value->setText(D_Value);
    D_Value_d = D_Value.toDouble();
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

}

void MainWindow::show_list_menu()
{
    QMenu *menu = new QMenu(ui->listWidget);
    QAction *deleteItem = new QAction("Delete", ui->listWidget);
    QAction *renameItem = new QAction("Rename", ui->listWidget);
    menu->addAction(renameItem);
    connect(renameItem, SIGNAL(triggered()), this, SLOT(rename()));
    menu->addAction(deleteItem);

    menu->move(cursor().pos());
    menu->show();


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
            // 将数据保存入全局矩阵中,解决行数大于8后，Matrix_x无法存储的错误
            if(i+r < 8 && j + c < 12){
                ui->tableWidget_excel->setItem(i+r,j+c,new QTableWidgetItem(q_str_list.at(q_str_list.size()/(count+1)*i+j)));
                Matrix_x(i+r,j+c) = ui->tableWidget_excel->item(i+r,j+c)->text().toDouble();
            }
        }
    }
    //std::cout << Matrix_x << std::endl;
}

void MainWindow::clear()
{
    ui->tableWidget_excel->clear();
    ui->listWidget->clear();
    group_count = 0;
}
//增加数据分组
void MainWindow::addgroup()
{
    //    选取选中的行列
    group_count +=1;
    QList<QTableWidgetSelectionRange> SelectedRange = ui->tableWidget_excel->selectedRanges();
    int r = SelectedRange.at(0).topRow();
    int c = SelectedRange.at(0).leftColumn();
    int rc = SelectedRange.at(0).rowCount();
    int cc = SelectedRange.at(0).columnCount();
    QColorDialog *qcd = new QColorDialog(this);
    QColor color = qcd->getColor("red",this,"选择颜色");
    for (int i = 0;i < rc; i++) {
        for (int j = 0;j < cc; j++) {
            ui->tableWidget_excel->item(i+r,j+c)->setBackground(color);
        }
    }
    QInputDialog *qid = new QInputDialog(this);
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    QString str = qid->getText(this,"输入分组名称对话框","请输入分组名称",echoMode, "group1");
    //    std::cout<<group1->getMatrix_G()<<std::endl;
    if(str.isEmpty()){
        ui->listWidget->addItem("group tmp");
    }else{
        ui->listWidget->addItem(str);
    }
    ui->listWidget->item(group_count-1)->setBackground(color);
    //    将分数据展示位table形式，便于观察
    QTableWidget *table = new QTableWidget(cc*rc, 3);

    //设置分组的列表头
    QStringList header;
    header<< "ReadValue"<<"MeanValue"<<"DrugConc";
    //设置分组的行表头
    QStringList VHeader;
    for (int i = 1; i < cc+1; i++) {
        QString str = QString::number(i,10);
        for (int j = 0;j<rc;j++) {
            VHeader.push_back(str);
        }
    }
    table->setVerticalHeaderLabels(VHeader);
    table->setHorizontalHeaderLabels(header);


    //    计算分组复空的均值
    QList<double> Qll;
    for (int j = 0; j < cc ; ++j) {
        double sum = 0;
        for (int i = 0; i < rc; ++i) {
            double tmp =  ui->tableWidget_excel->item(i+r, j+c)->text().toDouble();
            sum += tmp;
        }
        sum = sum/rc;
        //        qDebug() << sum;
        Qll.push_back(sum);
    }
    //根据药物的起始浓度S_value,计算在D_value稀释倍数下的药物稀释梯度

    QList<double> DrugValue;
    double DS_value = S_Value_d;
    for (int j = 0; j < cc; j ++) {
        DrugValue.push_back(DS_value);
        DS_value /= D_Value_d;
    }
    for (int i = 0; i < rc ; ++i) {
        for (int j = 0; j < cc; ++j) {
            QString str = ui->tableWidget_excel->item(i+r, j+c)->text();
            //            qDebug()<<str;
            try {
                table->setItem(i+rc*j,0,new QTableWidgetItem(str));
                table->item(i+rc*j,0)->setBackground(color);
                //                将计算出的均值加入分组的表格中
                QString str1 = QString("%1").arg(Qll.at(j));
                table->setItem(rc*j,1, new QTableWidgetItem(str1));
                //                将计算出的药物稀释梯度值加入到分组表格中
                QString str2 = QString("%1").arg(DrugValue.at(j));
                table->setItem(rc*j,2, new QTableWidgetItem(str2));



            } catch (...) {
            }
        }
    }
    qtw.push_back(table);

}
//实现右击菜单修改分组名称
void MainWindow::rename()
{
    QInputDialog *qid = new QInputDialog(this);
    QLineEdit::EchoMode echoMode=QLineEdit::Normal;
    QString str = qid->getText(this,"输入分组名称对话框","请输入分组名称",echoMode, "group");
    QList<QListWidgetItem*> qlwi = ui->listWidget->selectedItems();
    qlwi.first()->setText(str);

}


void MainWindow::on_dataFit_btn_clicked()
{
    int rc = qtw.at(0)->rowCount();
    QVector<double> vecMean;
    for (int i = 0;i < rc; i++) {
        try {
            if(qtw.at(0)->item(i,1)!=nullptr){
                double tmp = qtw.at(0)->item(i,1)->text().toDouble();
                vecMean.push_back(tmp);
            }
        } catch (...) {
        }
    }
    QVector<double> vecDilutionSeries;
    for (int i = 0;i < rc; i++) {
        if(qtw.at(0)->item(i,2)!=nullptr){
            double tmp = qtw.at(0)->item(i,2)->text().toDouble();
            vecDilutionSeries.push_back(tmp);
        }
    }
    //    qDebug()<<vecMean;
    //    qDebug()<<vecDilutionSeries;
    FourPLInitialValue *initialValue = new FourPLInitialValue(vecMean,vecDilutionSeries);

    //    qDebug()<< initialValue->getInitialA();
    //    qDebug()<< initialValue->getInitialB();
    //    qDebug()<< initialValue->getInitialC();
    //    qDebug()<< initialValue->getInitialD();

    LMmethod *LM = new LMmethod();
    //    double A =  3.181429e+03;
    //    double B =  1.501060e+00;
    //    double C =  1.658991e+00;
    //    double D =  2.373467e+05;
    //    double A =  100;
    //    double B =  100;
    //    double C =  100;
    //    double D =  100;
    MatrixXd ABCD = LM->LM(vecDilutionSeries,
                           vecMean,
                           initialValue->getInitialA(),
                           initialValue->getInitialB(),
                           initialValue->getInitialC(),
                           initialValue->getInitialD());



    //    ui->tableWidget_parameter->setItem(0,0, new QTableWidgetItem(1234));
    for (int i = 0; i < ABCD.rows();i++) {
        double tmp = ABCD(i,0);
        QString str = QString::number(tmp);
        ui->tableWidget_parameter->setItem(i,0, new QTableWidgetItem(str));
    }
    double rsq = LM->Rsquare(vecDilutionSeries,
                             vecMean,
                             ABCD(0,0),
                             ABCD(1,0),
                             ABCD(2,0),
                             ABCD(3,0));


    QString str = QString::number(rsq);
    ui->tableWidget_parameter->setItem(4,0, new QTableWidgetItem(str));
    //绘制图表
    FourParameterFunction *FPF = new FourParameterFunction();
    QSplineSeries *series = new QSplineSeries();
    series->setName("spline");
    QVector<double> Yplotdata = FPF->FourPLFunction(vecDilutionSeries,
                                                    ABCD(0,0),
                                                    ABCD(1,0),
                                                    ABCD(2,0),
                                                    ABCD(3,0));
    for (int i = 0; i< Yplotdata.size();i ++) {
        series->append(log10(vecDilutionSeries.at(i)),Yplotdata.at(i));
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("D+(A-D)/(1+(x/C)^B)");
    chart->createDefaultAxes();
//    chart->axisY()->setRange(0, 10);
//    QChartView *chartView = new QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);
    ui->widget_7->setChart(chart);
    //    FourParameterFunction *FPF = new FourParameterFunction();


    //    LevenbergMarquarelt *LM = new LevenbergMarquarelt(vecDilutionSeries,vecMean,
    //                                                      initialValue->getInitialA(),
    //                                                      initialValue->getInitialB(),
    //                                                      initialValue->getInitialC(),
    //                                                      initialValue->getInitialD());
    //    cout<<FPF->JocabiMatrix(vecDilutionSeries,
    //                      100,
    //                      1,
    //                      5,
    //                      2000)<<endl;
    //    cout << LM->Ep_update(vecDilutionSeries,vecMean,
    //                          initialValue->getInitialA(),
    //                          initialValue->getInitialB(),
    //                          initialValue->getInitialC(),
    //                          initialValue->getInitialD()) << endl;
    //    cout <<  << endl;
    //    cout << LM->LM() << endl;
    //     cout << LM->Po() << endl;

    //    LevenbergMarquarelt *LM = new LevenbergMarquarelt();
    //    LM->setJ(vecDilutionSeries,
    //             initialValue->getInitialA(),
    //             initialValue->getInitialB(),
    //             initialValue->getInitialC(),
    //             initialValue->getInitialD());

    //   MatrixXd j  = LM->J();
    //   LM->setA();
    //   LM->setPo(initialValue->getInitialA(),
    //               initialValue->getInitialB(),
    //               initialValue->getInitialC(),
    //               initialValue->getInitialD());


    //   LM->setEp(vecDilutionSeries,
    //             vecMean,
    //             initialValue->getInitialA(),
    //             initialValue->getInitialB(),
    //             initialValue->getInitialC(),
    //             initialValue->getInitialD());
    //   cout << LM->infinite_norm(LM->Ep()) << "  "<<LM->Ep().lpNorm<Infinity>() << endl;
    //   LM->setG();
    //   LM->setMu();

    //   cout << LM->getMu() << endl;

    //    LM->setJ(vecDilutionSeries,
    //             initialValue->getInitialA(),
    //             initialValue->getInitialB(),
    //             initialValue->getInitialC(),
    //             initialValue->getInitialD());
    //    cout << LM->J() <<endl;
    //    cout << LM->Solve() <<endl;

}
//将分组数据展示在后面表格中
void MainWindow::on_pushButton_2_clicked()
{
    delete ui->settingtab->layout();

    QVBoxLayout *layout = new QVBoxLayout;
    for (int i = 0; i < qtw.size(); i++) {
        layout->addWidget(qtw.at(i));
    }
    ui->settingtab->setLayout(layout);
}
