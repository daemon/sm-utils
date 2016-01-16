#include <iomanip>
#include <iostream>
#include <utility>
#include "OdeSolver.hpp"
#include "OdeSystem.hpp"

using namespace sm_utils;

#ifndef EULER_TEST_STEPS 
  #define EULER_TEST_STEPS 10000000
#endif
#ifndef EULER_TEST_STEPSIZE 
  #define EULER_TEST_STEPSIZE 0.0000001
#endif


static void test(const OdeSystem& system, double start, double stepsize, double *values)
{
  double *originalValues = new double[system.size()];
  for (size_t i = 0; i < system.size(); ++i)
    originalValues[i] = values[i];
  StepperHints hints;
  createStepperHints(&hints, start, stepsize, values, system.size());
  for (int i = 0; i < EULER_TEST_STEPS; ++i)
  {
    euler1(system, &hints);
    for (size_t j = 0; j < system.size(); ++j)
    {
      hints.initialValues[j] = hints.output[j];
      hints.start += EULER_TEST_STEPSIZE;
    }
  }
  std::cout << std::setprecision(15) << "First-order Euler: " << hints.output[0] << std::endl;
  destroyStepperHints(&hints);
  StepperHints hints2;
  createStepperHints(&hints2, start, stepsize, originalValues, system.size());
  for (int i = 0; i < EULER_TEST_STEPS; ++i)
  {
    euler2(system, &hints2);
    for (size_t j = 0; j < system.size(); ++j)
    {
      hints2.initialValues[j] = hints2.output[j];
      hints2.start += EULER_TEST_STEPSIZE;
    }
  }
  std::cout << std::setprecision(15) << "Heun's method: " << hints2.output[0] << std::endl;
  destroyStepperHints(&hints2);
  delete[] originalValues;
}

static void testLorenz(const OdeSystem& system, double start, double stepsize, double *values)
{
  double *originalValues = new double[system.size()];
  for (size_t i = 0; i < system.size(); ++i)
    originalValues[i] = values[i];
  StepperHints hints;
  createStepperHints(&hints, start, stepsize, values, system.size());
  std::cout << "Euler's method:" << std::endl;
  for (int i = 0; i <= 100000000; ++i)
  {
    euler1(system, &hints);
    for (size_t j = 0; j < system.size(); ++j)
    {
      hints.initialValues[j] = hints.output[j];
      hints.start += EULER_TEST_STEPSIZE;
    }
    if (i != 0)
    {
      if (i % 5000000 == 0)
      {
        double n = i / (double) EULER_TEST_STEPS;
        std::cout << std::setprecision(15) << "x(" << n << ") = " << hints.output[0] << std::endl;
        std::cout << std::setprecision(15) << "y(" << n << ") = " << hints.output[1] << std::endl;
        std::cout << std::setprecision(15) << "z(" << n << ") = " << hints.output[2] << std::endl;
      }
    }
  }
  StepperHints hints2;
  createStepperHints(&hints2, start, stepsize, originalValues, system.size());
  std::cout << std::endl;
  std::cout << "Heun's method:" << std::endl;
  for (int i = 0; i <= 100000000; ++i)
  {
    euler2(system, &hints2);
    for (size_t j = 0; j < system.size(); ++j)
    {
      hints2.initialValues[j] = hints2.output[j];
      hints2.start += EULER_TEST_STEPSIZE;
    }
    if (i != 0)
    {
      if (i % 5000000 == 0)
      {
        double n = i / (double) EULER_TEST_STEPS;
        std::cout << std::setprecision(15) << "x(" << n << ") = " << hints2.output[0] << std::endl;
        std::cout << std::setprecision(15) << "y(" << n << ") = " << hints2.output[1] << std::endl;
        std::cout << std::setprecision(15) << "z(" << n << ") = " << hints2.output[2] << std::endl;
      }
    }
  }
  delete[] originalValues;
  destroyStepperHints(&hints);
  destroyStepperHints(&hints2);
}

int main(int argc, char **argv)
{
  OdeSystem system;
  system.addEquation([](double t, double *values) {
    return 2 * t;
  });
  std::cout << "Using stepsize=1E-7, start=0, target=1:" << std::endl;
  std::cout << "dy/dx = 2x, y(0) = 0" << std::endl;
  double value[1] = {0.0};
  test(system, 0, EULER_TEST_STEPSIZE, value);

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
  test(system, 0, EULER_TEST_STEPSIZE, values);

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
  testLorenz(system, 0, EULER_TEST_STEPSIZE, values);

  std::cout << std::endl;
  std::cout << "Exact answers:" << std::endl;
  std::cout << "(1) = 1" << std::endl;
  std::cout << "(2) = e^1 - 1 = 1.718281828459045" << std::endl;

  return 0;
}
