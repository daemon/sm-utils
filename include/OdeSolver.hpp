#ifndef _ODE_SOLVER_HPP
#define _ODE_SOLVER_HPP

#include <vector>
#include "Hints.hpp"

namespace sm_utils
{

class OdeSystem;

struct StepperHints
{
  double start;
  double *initialValues;
  double stepsize;
  double *output;
  double *dy1;
  double *dy2;
  double *dy3;
};

// Stepper hints
void createStepperHints(StepperHints *hints, double start, double stepsize, double *values, int nElements);
void destroyStepperHints(StepperHints *hints);

// Single-step, low-level methods
void euler1(const OdeSystem& system, StepperHints *hints) SM_ATTR_HOT;
void euler2(const OdeSystem& system, StepperHints *hints) SM_ATTR_HOT;

// Adaptive stepsize solvers
std::vector<double> euler12Solve(const OdeSystem &system, double t, double start, std::vector<double> initialValues, double tol=0.000001);
std::vector<double> rungeKutta45Solve(const OdeSystem &system, double t, double start, std::vector<double> initialValues, double tol=0.000001);

}

#endif
