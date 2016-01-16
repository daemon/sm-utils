#include <utility>
#include "OdeSystem.hpp"

using namespace sm_utils;

void sm_utils::OdeSystem::addEquation(OdeSystem::StepFn callback)
{
  this->_equations.push_back(std::move(callback));
}

void sm_utils::OdeSystem::eval(double t, double *values, double *dy) const
{
  int i = 0;
  for (auto &eq : this->_equations)
  {
    dy[i] = eq(t, values);
   	++i;
  }
}

double *sm_utils::OdeSystem::eval(double t, double *values) const
{
  double *dy = new double[this->size()];
  int i = 0;
  for (auto &eq : this->_equations)
  {
    dy[i] = eq(t, values);
    ++i;
  }
  return dy;
}
