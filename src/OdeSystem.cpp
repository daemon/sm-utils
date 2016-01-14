#include <utility>
#include "OdeSystem.hpp"

using namespace sm_utils;

void sm_utils::OdeSystem::addEquation(OdeSystem::StepFn callback)
{
  this->_equations.push_back(std::move(callback));
}

std::vector<double> sm_utils::OdeSystem::eval(double t, std::vector<double> values)
{
  std::vector<double> dy;
  for (auto &eq : this->_equations)
    dy.push_back(eq(t, values));

  return dy;
}
