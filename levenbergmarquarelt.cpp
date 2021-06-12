#include "levenbergmarquarelt.h"
#include "fourparameterfunction.h"
#include <Eigen/Dense>
#include "fourparameterfunction.h"
#include "fourplinitialvalue.h"
#include <algorithm>
#include <math.h>
#include <numeric>

using namespace std;
using namespace Eigen;

MatrixXd LevenbergMarquarelt::A() const
{
    return A_;
}

void LevenbergMarquarelt::setA()
{
    MatrixXd A_tmp = this->J_.transpose()*this->J_;
    A_ = A_tmp;
}

MatrixXd LevenbergMarquarelt::J() const
{
    return J_;
}

void LevenbergMarquarelt::setJ(QVector<double> vec, double A, double B, double C, double D)
{
    FourParameterFunction *FPF = new FourParameterFunction();
    MatrixXd J_tmp = FPF->JocabiMatrix(vec, A, B, C, D);
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

    Ep_.resize(Ep_tmp.size(),1);
    for(int i = 0; i < Yd.size(); i++){
        Ep_(i, 1) = Ep_tmp.at(i);
    }

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

MatrixXd LevenbergMarquarelt::getG() const
{
    return g_;
}

void LevenbergMarquarelt::setG()
{
    MatrixXd g_tmp = this->J_.transpose()*this->Ep_;
    g_ = g_tmp;
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
    MatrixXd L_matrix = this->A_ +this->mu* (MatrixXd::Identity(this->A_.rows(), this->A_.cols()));
    this->deltaP = L_matrix.inverse()*(-this->g_);
    return this->deltaP;
}

VectorXd LevenbergMarquarelt::LM()
{
    FourParameterFunction *FPF = new FourParameterFunction();
    this->stop = this->infinite_norm(this->g_) <= this->e1;
    double mu = this->mu;
    while (!stop && this->k < this->k_max) {
        k++;
        this->Solve();
        this->P = this->Po_;
        if(this->two_norm(this->deltaP) <= this->two_norm(this->P)){
            this->stop = true;
        }else {
            VectorXd P_new = this->P + this->deltaP;
            VectorXd Ep_update = this->Ep(this->Xd,
                                          this->Yd,
                                          P_new(0),
                                          P_new(1),
                                          P_new(2),
                                          P_new(3));
            this->rho = (pow(this->two_norm(this->Ep_), 2) -
                         pow(this->two_norm(Ep_update), 2)) /
                    (this->deltaP.transpose()*(mu*this->deltaP + this->g_));
            if(rho > 0){
                this -> P = P_new;
                MatrixXd J_tmp = FPF->JocabiMatrix(this->Xd, this->P(0),this->P(1),this->P(2),this->P(3));
                this->A_ = J_tmp.transpose()*J_tmp;
                VectorXd update_EP;
                update_EP = this->Ep(this->Xd,
                                     this->Yd,
                                     this->P(0),
                                     this->P(1),
                                     this->P(2),
                                     this->P(3));
                this->g_ = this->g_.transpose()*update_EP;
                this->stop = (this->infinite_norm(this->g_) <= this->e1) || (pow(this->two_norm(update_EP),2) <= this->e3);
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
        if(this->rho > 0 || this->stop)
            break;

    }
    return this->P;
}

VectorXd LevenbergMarquarelt::Ep(QVector<double> Xd, QVector<double> Yd, double A, double B, double C, double D)
{
    FourParameterFunction *FPF = new FourParameterFunction();
    QVector<double> Yd_ = FPF->FourPLFunction(Xd, A, B, C, D);
    QVector<double> Ep_tmp;
    for(int i = 0; i < Yd.size(); i++){
        Ep_tmp.push_back(Yd.at(i) - Yd_.at(i));
    }
    VectorXd Ep_update;
    Ep_update.resize(Ep_tmp.size(),1);
    for(int i = 0; i < Yd.size(); i++){
        Ep_(i, 1) = Ep_tmp.at(i);
    }
    return Ep_update;
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
    sum = accumulate(tmp.begin(),tmp.end(),0.0);
    return sum;
}




