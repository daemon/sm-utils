#include <cstring>
#include "OdeSolver.hpp"
#include "OdeSystem.hpp"

using namespace sm_utils;

double *sm_utils::euler1(const OdeSystem &system, double start, double stepsize, double *initialValues)
{
  double *dy = system.eval(start, initialValues);
  double *solutions = new double[system.size()];
  for (size_t i = 0; i < system.size(); ++i)
    solutions[i] = initialValues[i] + stepsize * dy[i];
  delete[] dy;
  return solutions;
}

double *sm_utils::euler2(const OdeSystem &system, double start, double stepsize, double *initialValues)
{
  double *dy1 = system.eval(start, initialValues);
  double *ystar = euler1(system, start, stepsize, initialValues);
  double *dy2 = system.eval(start + stepsize, ystar);
  delete[] ystar;
  double h2 = stepsize / 2;
  double *solutions = new double[system.size()];
  for (size_t i = 0; i < system.size(); ++i)
    solutions[i] = initialValues[i] + h2 * (dy2[i] + dy1[i]);
  delete[] dy2;
  delete[] dy1;
  return solutions;
}

double *sm_utils::euler12Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol)
{
  // STUB
  return nullptr;
}

double *sm_utils::rungeKutta45Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol)
{
  // STUB
  return nullptr;
}
