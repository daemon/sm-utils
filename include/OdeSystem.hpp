#ifndef _ODE_SYSTEM_HPP
#define _ODE_SYSTEM_HPP

#include <functional>
#include <vector>

namespace sm_utils
{

/**
  * Dynamics function in canonical form
  */
class OdeSystem
{
public:
  using StepFn = std::function<double(double t, double *values)>;
  void addEquation(StepFn callback);
  size_t size() const { return this->_equations.size(); }
  double *eval(double t, double *values) const;

private:
  std::vector<StepFn> _equations;
};

}

#endif
