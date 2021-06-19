#include "lmmethod.h"
#include "levenbergmarquarelt.h"
#include "fourparameterfunction.h"
#include <Eigen/Dense>
#include "fourplinitialvalue.h"
#include <algorithm>
#include <math.h>
#include <numeric>
#include <QDebug>
#include <iostream>
using namespace std;
LMmethod::LMmethod()
{

}


VectorXd LMmethod::LM(QVector<double> X, QVector<double> Y, double A, double B, double C, double D)
{
    FourParameterFunction *FPF = new FourParameterFunction();
    bool found;
    double e1 = 1e-15;
    double e2 = 1e-15;
    double tao = 1e-6;
    int k = 0;
    int v = 2;
    int Kmax = 100;
    double rho;
    Vector4d Po;
    Vector4d P;
    Vector4d deltaP;
    Po.resize(4,1);
    Po(0,0) = A;
    Po(1,0) = B;
    Po(2,0) = C;
    Po(3,0) = D;
    P = Po;
    MatrixXd J;
    J.resize(X.size(), 4);
    J = FPF->JocabiMatrix(X, A, B, C, D);
    MatrixXd Am;
    Am.resize(J.transpose().rows(),J.cols());
    Am = J.transpose()*J;
    VectorXd f;
    f.resize(X.size(),1);
    f = Ep(X, Y, A, B, C, D);
    VectorXd g;
    g.resize(J.transpose().rows(), 1);
    g = J.transpose()*f;
    found = infinite_norm(g) <= e1;
//    qDebug() <<  "found = infinite_norm(g) <= e1";
//    qDebug() << infinite_norm(g);
    double mu;
    mu = setMu(Am, tao);
    while(!found && k < Kmax)
    {
        k = k + 1;
//        qDebug()<<k;
//        qDebug() << k;
//        qDebug()<< mu;
        deltaP = Solve(Am, g, mu);
//        cout << "P" << endl;
//        cout << P << endl;
//        qDebug() << "two_norm(deltaP) <= e2*(two_norm(P) + e2)";
//        qDebug()<< deltaP.norm() << e2*(two_norm(P) + e2);
        if(two_norm(deltaP) <= e2*(two_norm(P) + e2))
        {
            found = true;
        }
        else
        {
            Vector4d P_new = P + deltaP;
            VectorXd FX;
            FX.resize(X.size(),1);
            FX = Ep(X,
                    Y,
                    P(0,0),
                    P(1,0),
                    P(2,0),
                    P(3,0));
            VectorXd FX_new;
            FX_new.resize(X.size(),1);
            FX_new = Ep(X,
                        Y,
                        P_new(0,0),
                        P_new(1,0),
                        P_new(2,0),
                        P_new(3,0));

            MatrixXd FU = 0.5*FX.transpose()*FX - 0.5*FX_new.transpose()*FX_new;
            MatrixXd LD = -deltaP.transpose()*J.transpose()*FX - 0.5 * deltaP.transpose()*J.transpose()*J*deltaP;
            rho = FU(0,0)/LD(0,0);

//            qDebug()<<rho;
            if(rho > 0)
            {
//                qDebug()<<"到此";
                P = P_new;
                J = FPF->JocabiMatrix(X,
                                      P(0,0),
                                      P(1,0),
                                      P(2,0),
                                      P(3,0));
                Am = J.transpose()*J;
                f = Ep(X,
                       Y,
                       P(0,0),
                       P(1,0),
                       P(2,0),
                       P(3,0));
                g = J.transpose()*f;
                found = infinite_norm(g) <= e1;
                mu = mu*max<double>(1/3, 1-pow((2*rho - 1),3));
                v = 2;
            }
            else {
//                qDebug()<<"到此";
                mu = mu*v;
                v = 2*v;
            }
        }
//        cout << P << endl;
    }
    return P;
}

VectorXd LMmethod::Ep(QVector<double> Xd, QVector<double> Yd, double A, double B, double C, double D)
{
    FourParameterFunction *FPF = new FourParameterFunction();
    QVector<double> Yd_ = FPF->FourPLFunction(Xd,A,B,C,D);
    QVector<double> Ep_tmp;
    for(int i = 0; i < Yd.size(); i++){
        Ep_tmp.push_back(Yd.at(i) - Yd_.at(i));
    }
    VectorXd Ep_tmp_;
    Ep_tmp_.resize(Ep_tmp.size(),1);
    for(int i = 0; i < Ep_tmp.size(); i++){
        Ep_tmp_(i, 0) = Ep_tmp.at(i);
    }
    return Ep_tmp_;
    //    FourParameterFunction *FPF = new FourParameterFunction();
    //    QVector<double> Yd_ = FPF->FourPLFunction(Xd, A, B, C, D);
    //    QVector<double> Ep_tmp;
    //    for(int i = 0; i < Yd.size(); i++){
    //        Ep_tmp.push_back(Yd.at(i) - Yd_.at(i));
    //    }
    //    VectorXd Ep_update;
    //    Ep_update.resize(Yd.size(),1);
    //    for(int i = 0; i < Yd.size(); i++){
    //        Ep_update(i, 0) = Ep_tmp.at(i);
    //    }
    //    return Ep_update;
}

double LMmethod::infinite_norm(MatrixXd g_)
{
    double max;
    QVector<double> tmp;
    for(int i= 0; i < g_.rows(); i++ ){
        for(int j = 0; j < g_.cols(); j++){
            double num = abs(g_(i,j));
            tmp.push_back(num);
        }
    }
    max = *max_element(tmp.begin(),tmp.end());
    return max;
}

double LMmethod::two_norm(MatrixXd g_)
{
    double sum;
    QVector<double> tmp;
    for(int i= 0; i < g_.rows(); i++ ){
        for(int j = 0; j < g_.cols(); j++){
            double num = pow(g_(i,j),2);
            tmp.push_back(num);
        }
    }
    sum = pow(accumulate(tmp.begin(),tmp.end(),0.0),0.5);
    return sum;
}

VectorXd LMmethod::Solve(MatrixXd A, MatrixXd g, double mu)
{

    Matrix4d L_matrix = A + mu * (MatrixXd::Identity(A.rows(), A.cols()));
    //    cout << L_matrix << endl;
    //    cout << L_matrix.inverse()*L_matrix << endl;
    Vector4d delta_tmp;
    //    delta_tmp = L_matrix.ldlt().solve(-this->g_);
    Vector4d Z;
//    delta_tmp = L_matrix.inverse()*(-1*g);
    delta_tmp = L_matrix.ldlt().solve(-1*g);
    return delta_tmp;
}

double LMmethod::setMu(MatrixXd A, double tao)
{

    QVector<double> vec;
    for(int i = 0; i < A.rows(); i++){
        vec.push_back(A(i,i));
    }
    double mu_tmp = tao*(*max_element(vec.begin(),vec.end()));
    return mu_tmp;
}
