#ifndef _ODE_SOLVER_HPP
#define _ODE_SOLVER_HPP

#include <vector>

namespace sm_utils
{

class OdeSystem;

std::vector<double> euler1(OdeSystem system, double start, double stepsize, std::vector<double> initialValues);
std::vector<double> euler2(OdeSystem system, double start, double stepsize, std::vector<double> initialValues);
std::vector<double> euler12Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol=0.000001);
std::vector<double> rungeKutta45Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol=0.000001);

}

#endif
