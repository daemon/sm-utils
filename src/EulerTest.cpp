#include <iomanip>
#include <iostream>
#include <utility>
#include "OdeSolver.hpp"
#include "OdeSystem.hpp"

using namespace sm_utils;

static void test(const OdeSystem& system, double start, double stepsize, double *values)
{
  double *originalVals = values;
  double *solutions;
  for (int i = 0; i < 100000000; ++i)
  {
    solutions = euler1(system, start + i * stepsize, stepsize, values);
    if (i != 0)
      delete[] values;
    values = solutions;
  }
  std::cout << std::setprecision(31) << "First-order Euler: " << solutions[0] << std::endl;
  delete[] solutions;
  values = originalVals;
  for (int i = 0; i < 100000000; ++i)
  {
    solutions = euler2(system, start + i * stepsize, stepsize, values);
    if (i != 0)
      delete[] values;
    values = solutions;
  }
  std::cout << std::setprecision(31) << "Heun's method: " << solutions[0] << std::endl;
  delete[] solutions;
}

int main(int argc, char **argv)
{
  OdeSystem system;
  system.addEquation([](double t, double *values) {
    return 2 * t;
  });
  std::cout << "Using stepsize=1E-8, start=0, target=1:" << std::endl;
  std::cout << "dy/dx = 2x, y(0) = 0" << std::endl;
  test(system, 0, 0.00000001, new double[1]());

  system = OdeSystem();
  system.addEquation([](double t, double *values) {
    return values[1];
  });
  system.addEquation([](double t, double *values) {
    return values[1];
  });
  std::cout << std::endl;
  std::cout << "y' = y'', y(0) = 0, y'(0) = 1" << std::endl;
  double *values = new double[2];
  values[0] = 0;
  values[1] = 1;
  test(system, 0, 0.00000001, values);

  std::cout << std::endl;
  std::cout << "Exact answers:" << std::endl;
  std::cout << "(1) = 1" << std::endl;
  std::cout << "(2) = e^1 - 1 = 1.71828182845904523536028747135266" << std::endl;

  return 0;
}
