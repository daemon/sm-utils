#include "OdeSolver.hpp"
#include "OdeSystem.hpp"

using namespace sm_utils;

std::vector<double> sm_utils::euler1(OdeSystem system, double start, double stepsize, std::vector<double> initialValues)
{
  std::vector<double> dy = system.eval(start, initialValues);
  auto it = initialValues.begin();
  for (auto &i : dy)
  {
    *it += stepsize * i;
    ++it;
  }
  return initialValues;
}

std::vector<double> sm_utils::euler2(OdeSystem system, double start, double stepsize, std::vector<double> initialValues)
{
  std::vector<double> dy1 = system.eval(start, initialValues);
  std::vector<double> ystar = euler1(system, start + stepsize, stepsize, initialValues);
  std::vector<double> dy2 = system.eval(start + stepsize, ystar);
  auto it = initialValues.begin();
  auto dy2it = dy2.begin();
  double h2 = stepsize / 2;
  for (auto &i : dy1)
  {
    *it += h2 * (*dy2it + i);
    ++it;
    ++dy2it;
  }
  return initialValues;
}

std::vector<double> sm_utils::euler12Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol)
{
  // STUB
  return std::vector<double>();
}

std::vector<double> sm_utils::rungeKutta45Solve(OdeSystem system, double t, double start, std::vector<double> initialValues, double tol)
{
  // STUB
  return std::vector<double>();
}
