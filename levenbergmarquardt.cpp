#include "levenbergmarquardt.h"
#include "Eigen/Core"
#include "fourparameterfunction.h"
LevenbergMarquardt::LevenbergMarquardt()
{

}

Eigen::MatrixX4d LevenbergMarquardt::jacobian(Eigen::MatrixXd J_A,
                                              Eigen::MatrixXd J_B,
                                              Eigen::MatrixXd J_C,
                                              Eigen::MatrixXd J_D)
{

}

