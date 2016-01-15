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
  for (int i = 0; i < 10000000; ++i)
  {
    solutions = euler1(system, start + i * stepsize, stepsize, values);
    if (i != 0)
      delete[] values;
    values = solutions;
  }
  std::cout << std::setprecision(15) << "First-order Euler: " << solutions[0] << std::endl;
  delete[] solutions;
  values = originalVals;
  for (int i = 0; i < 10000000; ++i)
  {
    solutions = euler2(system, start + i * stepsize, stepsize, values);
    if (i != 0)
      delete[] values;
    values = solutions;
  }
  std::cout << std::setprecision(15) << "Heun's method: " << solutions[0] << std::endl;
  delete[] solutions;
}

static void testLorenz(const OdeSystem& system, double start, double stepsize, double *values)
{
  double *originalVals = values;
  double *solutions;
  std::cout << "Euler's method:" << std::endl;
  for (int i = 0; i <= 100000000; ++i)
  {
    solutions = euler1(system, start + i * stepsize, stepsize, values);
    if (i != 0)
    {
      if (i % 5000000 == 0)
      {
        double n = i / 10000000.0;
        std::cout << std::setprecision(15) << "x(" << n << ") = " << solutions[0] << std::endl;
        std::cout << std::setprecision(15) << "y(" << n << ") = " << solutions[1] << std::endl;
        std::cout << std::setprecision(15) << "z(" << n << ") = " << solutions[2] << std::endl;
      }
      delete[] values;
    }
    values = solutions;
  }
  delete[] solutions;
  values = originalVals;
  std::cout << std::endl;
  std::cout << "Heun's method:" << std::endl;
  for (int i = 0; i <= 100000000; ++i)
  {
    solutions = euler2(system, start + i * stepsize, stepsize, values);
    if (i != 0)
    {
      if (i % 5000000 == 0)
      {
        double n = i / 10000000.0;
        std::cout << std::setprecision(15) << "x(" << n << ") = " << solutions[0] << std::endl;
        std::cout << std::setprecision(15) << "y(" << n << ") = " << solutions[1] << std::endl;
        std::cout << std::setprecision(15) << "z(" << n << ") = " << solutions[2] << std::endl;
      }
      delete[] values;
    }
    values = solutions;
  }
  delete[] solutions;
}

int main(int argc, char **argv)
{
  OdeSystem system;
  system.addEquation([](double t, double *values) {
    return 2 * t;
  });
  std::cout << "Using stepsize=1E-7, start=0, target=1:" << std::endl;
  std::cout << "dy/dx = 2x, y(0) = 0" << std::endl;
  test(system, 0, 0.0000001, new double[1]());

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
  test(system, 0, 0.0000001, values);

  system = OdeSystem();
  system.addEquation([](double t, double *values) {
    return 10 * (values[1] - values[0]);
  });
  system.addEquation([](double t, double *values) {
    return values[0] * (28 - values[2]) - values[1];
  });
  system.addEquation([](double t, double *values) {
    return values[0] * values[1] - (8.0 / 3) * values[2];
  });
  values = new double[3];
  values[0] = 1;
  values[1] = 1;
  values[2] = 1;
  std::cout << std::endl;
  std::cout << "Lorenz attractor (sigma = 10, beta = 8/3, rho = 28)" << std::endl;
  testLorenz(system, 0, 0.0000001, values);

  std::cout << std::endl;
  std::cout << "Exact answers:" << std::endl;
  std::cout << "(1) = 1" << std::endl;
  std::cout << "(2) = e^1 - 1 = 1.718281828459045" << std::endl;

  return 0;
}
