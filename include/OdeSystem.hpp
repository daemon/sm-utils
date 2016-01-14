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
  using StepFn = std::function<double(double t, std::vector<double> values)>;
  void addEquation(StepFn callback);
  std::vector<double> eval(double t, std::vector<double> values);

private:
  std::vector<StepFn> _equations;
};

}

#endif
