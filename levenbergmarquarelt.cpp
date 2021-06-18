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
using namespace Eigen;

MatrixXd LevenbergMarquarelt::A() const
{
    return A_;
}

void LevenbergMarquarelt::setA()
{
    Matrix4d A_tmp = this->J_.transpose()*this->J_;
    A_ = A_tmp;
}

MatrixXd LevenbergMarquarelt::J() const
{
    return J_;
}

void LevenbergMarquarelt::setJ(QVector<double> vec, double A, double B, double C, double D)
{
    FourParameterFunction *FPF = new FourParameterFunction();
    MatrixXd J_tmp;
    J_tmp.resize(vec.size(), 4);
    J_tmp = FPF->JocabiMatrix(vec, A, B, C, D);
    J_ = J_tmp;
}

VectorXd LevenbergMarquarelt::Po() const
{
    return Po_;
}

void LevenbergMarquarelt::setPo(double A, double B, double C, double D)
{
    Vector4d Po_tmp(A, B, C, D);
    Po_ = Po_tmp;
}

VectorXd LevenbergMarquarelt::Ep() const
{
    return Ep_;
}

void LevenbergMarquarelt::setEp(QVector<double> Xd, QVector<double> Yd, double A, double B, double C, double D)
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
    Ep_ = Ep_tmp_;
}

double LevenbergMarquarelt::getMu() const
{
    return mu;
}

void LevenbergMarquarelt::setMu()
{
    MatrixXd A_tmp = this->A();
    QVector<double> vec;
    for(int i = 0; i < A_tmp.rows(); i++){
        vec.push_back(A_tmp(i,i));
    }
    double mu_tmp = this->tao*(*max_element(vec.begin(),vec.end()));
    mu = mu_tmp;
}

VectorXd LevenbergMarquarelt::getG() const
{
    return g_;
}

void LevenbergMarquarelt::setG()
{
    Vector4d g_tmp = this->J_.transpose()*this->Ep_;
    g_ = g_tmp;
}
LevenbergMarquarelt::LevenbergMarquarelt()
{

}

LevenbergMarquarelt::LevenbergMarquarelt(QVector<double> X, QVector<double> Y, double A, double B, double C, double D)
{
    this->Xd = X;
    this->Yd = Y;
    this->setPo(A,B,C,D);
    this->setJ(X,A,B,C,D);
    this->setA();
    this->setEp(X,Y,A,B,C,D);
    this->setG();
    this->setMu();


}

VectorXd LevenbergMarquarelt::Solve()
{
//    cout << this->A_<< endl;
//    cout << this->mu<< endl;
//    cout << this->g_ << endl;
//    cout << -this->g_ << endl;

//    cout << MatrixXd::Identity(this->A_.rows(), this->A_.cols()) << endl;


    Matrix4d L_matrix = this->A_ +this->mu* (MatrixXd::Identity(this->A_.rows(), this->A_.cols()));
//    cout << L_matrix << endl;
//    cout << L_matrix.inverse()*L_matrix << endl;
    Vector4d delta_tmp;
//    delta_tmp = L_matrix.ldlt().solve(-this->g_);
    delta_tmp = L_matrix.inverse()*(-this->g_);
    this->deltaP = delta_tmp;
    return delta_tmp;
}

VectorXd LevenbergMarquarelt::LM()
{
    FourParameterFunction *FPF = new FourParameterFunction();
    this->P = this->Po_;
    this->stop = this->infinite_norm(this->g_) <= this->e1;

    while (!stop && this->k < this->k_max) {
                qDebug()<<k;
        this->k++;
        this->Solve();
//        cout << this->Solve() << endl;
        cout << "******"<<endl;
        //        qDebug() << this->two_norm(this->deltaP);
        //        qDebug() << this->two_norm(this->P);
        if(this->two_norm(this->deltaP) <= this->e2*(this->two_norm(this->P) + this->e2)){
            this->stop = true;
        }else {


            Vector4d P_new = this->P + this->deltaP;



//            this->P = P_new;
//            cout<< this->P <<endl;
//            cout << "******"<<endl;
            VectorXd Ep_up;
            Ep_up.resize(this->Xd.size(),1);
            Ep_up = this->Ep_update(this->Xd,
                                    this->Yd,
                                    P_new(0,0),
                                    P_new(1,0),
                                    P_new(2,0),
                                    P_new(3,0));

//            cout << "P_new" << endl;
//            cout << Ep_up << endl;


//            cout << "P_new" << endl;

//            MatrixXd J_tmp;
//            J_tmp.resize(this->J_.rows(), 4);
//            J_tmp  = FPF->JocabiMatrix(this->Xd,
//                                       P_new(0,0),
//                                       P_new(1,0),
//                                       P_new(2,0),
//                                       P_new(3,0));

//            this->A_ = J_tmp.transpose()*J_tmp;
//            this->g_ = J_tmp.transpose()*Ep_up;

            //            cout << Ep_update << endl;
            //            cout << this->Ep_ << endl;
            //            qDebug() << pow(this->two_norm(this->Ep_), 2);
            //            qDebug() << pow(this->two_norm(Ep_update), 2);
            //            qDebug() << this->deltaP.transpose()*(mu*this->deltaP + this->g_);

            this->rho =(this->two_norm(this->Ep_) - this->two_norm(Ep_up)) /
                   (0.5*this->deltaP.transpose()*(this->mu*this->deltaP - this->g_));

//            cout << "this->deltaP.transpose()*(this->mu*this->deltaP - this->g_)" <<endl;
//            cout << this->two_norm(Ep_up)  <<endl;
//            cout << this->deltaP.transpose()*(this->mu*this->deltaP - this->g_) <<endl;
//            cout << "this->deltaP.transpose()*(this->mu*this->deltaP - this->g_)" <<endl;
                        qDebug() << rho;
            if(rho > 0){
                this -> P = P_new;
                this->setJ(this->Xd,
                           P_new(0,0),
                           P_new(1,0),
                           P_new(2,0),
                           P_new(3,0));
                this->setA();
                this->setEp(this->Xd,
                            this->Yd,
                            P_new(0,0),
                            P_new(1,0),
                            P_new(2,0),
                            P_new(3,0));
                this->setG();

                this->stop = (this->infinite_norm(this->g_) <= this->e1);
                double max_number;
                if(1/3 < (1 - pow((this->rho*2 - 1), 3))){
                    max_number = 1 - pow((this->rho*2 - 1), 3);
                }else{
                    max_number = 1/3;
                }
                this->mu = this->mu * max_number;
                this->v = 2;

            }else{
                this->mu = this->mu * this->v;
                this->v = this->v * 2;
            }
        }
        //        if(this->rho > 0 || this->stop)
        //            break;
//        cout << this->P<<endl;

    }
    return this->P;
}

VectorXd LevenbergMarquarelt::Ep_update(QVector<double> Xd,
                                        QVector<double> Yd,
                                        double A,
                                        double B,
                                        double C,
                                        double D)
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

double LevenbergMarquarelt::infinite_norm(MatrixXd g_)
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

double LevenbergMarquarelt::two_norm(MatrixXd g_)
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





