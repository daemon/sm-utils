#include <cmath>
#include <cstring>
#include "OdeSolver.hpp"
#include "OdeSystem.hpp"

using namespace sm_utils;

void sm_utils::createStepperHints(StepperHints *hints, double start, double stepsize, double *values, int nElements)
{
  hints->start = start;
  hints->stepsize = stepsize;
  hints->initialValues = values;
  hints->output = new double[nElements * 4];
  hints->dy1 = hints->output + nElements;
  hints->dy2 = hints->output + 2 * nElements;
  hints->dy3 = hints->output + 3 * nElements;
}

void sm_utils::destroyStepperHints(StepperHints *hints)
{
  delete[] hints->output;
}

void sm_utils::euler1(const OdeSystem &system, StepperHints *hints)
{
  system.eval(hints->start, hints->initialValues, hints->dy1);
  for (size_t i = 0; i < system.size(); ++i)
    hints->output[i] = hints->initialValues[i] + hints->stepsize * hints->dy1[i];
}

void sm_utils::euler2(const OdeSystem &system, StepperHints *hints)
{
  double start = hints->start;
  double *initialValues = hints->initialValues;
  double stepsize = hints->stepsize;
  system.eval(start, initialValues, hints->dy3);
  euler1(system, hints);
  system.eval(start + stepsize, hints->output, hints->dy2);
  double h2 = stepsize / 2;
  for (size_t i = 0; i < system.size(); ++i)
    hints->output[i] = initialValues[i] + h2 * (hints->dy3[i] + hints->dy2[i]);
}

std::vector<double> sm_utils::euler12Solve(const OdeSystem &system, double t, double start, std::vector<double> initialValues, double tol)
{
  /*double *values = &initialValues[0];
  double *ylow = euler1(system, start, 0.01, values);
  double *yhigh = euler2(system, start, 0.01, values);
  double hnew = 0.01 * (0.8 * tol / abs(ylow[0] - yhigh[0])); // arbitrary guess*/
  return std::vector<double>();
}

std::vector<double> sm_utils::rungeKutta45Solve(const OdeSystem &system, double t, double start, std::vector<double> initialValues, double tol)
{
  // STUB
  return std::vector<double>();
}
