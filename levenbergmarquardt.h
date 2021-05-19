#ifndef LEVENBERGMARQUARDT_H
#define LEVENBERGMARQUARDT_H
#include "Eigen/Core"
#include "Eigen/Geometry"
#include "fourparameterfunction.h"

class LevenbergMarquardt
{
public:

    Eigen::MatrixX4d jacobian(Eigen::MatrixXd J_A,
                              Eigen::MatrixXd J_B,
                              Eigen::MatrixXd J_C,
                              Eigen::MatrixXd J_D);
    LevenbergMarquardt();
    ~LevenbergMarquardt();

};

#endif // LEVENBERGMARQUARDT_H
