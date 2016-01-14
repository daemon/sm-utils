#ifndef _ODE_SOLVER_HPP
#define _ODE_SOLVER_HPP

#include <vector>

namespace sm_utils
{

class OdeSystem;

double *euler1(const OdeSystem& system, double start, double stepsize, double *initialValues);
double *euler2(const OdeSystem& system, double start, double stepsize, double *initialValues);
double *euler12Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol=0.000001);
double *rungeKutta45Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol=0.000001);

}

#endif
