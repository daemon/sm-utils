#include <iostream>
#include "OdeSolver.hpp"
#include "OdeSystem.hpp"

using namespace sm_utils;

int main(int argc, char **argv)
{
  OdeSystem system;
  system.addEquation([](double t, std::vector<double> values) {
    return t * t;
  });
  /*system.addEquation([](double t, std::vector<double> values) {
    return 3 * values[0];
  });*/
  std::vector<double> solutions = euler1(system, 1, 1, {1, 0});
  std::cout << "First-order Euler: " << solutions[0] << ", " << solutions[1] << std::endl;
  solutions = euler2(system, 1, 1, {1, 0});
  std::cout << "Heun's method: " << solutions[0] << ", " << solutions[1] << std::endl;
  return 0;
}
