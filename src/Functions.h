#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Types.h"
#include <Eigen/Core>
#include <cmath>

namespace MetaOpt {

/**
 * N-Dimensional generalization of the Rosenbrock function
 *
 * The minimum of this function will be at zero
 *
 * @param vec :: n dimensional array of x values
 * @return value of the function evaluated at the point defined by vec
 */
double rosen(const Parameters &params) {
  using namespace std;
  double y = 0;
  for (size_t i = 0; i < params.size() - 1; ++i) {
    const double x1 = params.at("x" + std::to_string(i));
    const double x2 = params.at("x" + std::to_string(i + 1));
    y += 100 * pow(x2 - pow(x1, 2.0), 2.0) + pow(1 - x1, 2.0);
  }

  return y;
}

/**
 * N-Dimensional parabolic function centered on the origin.
 *
 * The function has the form x1**2 + x2**2 + ... + xn**2 = y
 *
 * The minimum of this function will be at zero
 *
 * @param vec :: n dimensional arry of x values
 * @return value of the function evaludated at the point defined by vec
 */
double parabola(const Parameters &params) {
  using namespace std;
  double y = 0;
  for (const auto &param : params)
    y += std::pow(param.second, 2.0);

  return y;
}
}
#endif // FUNCTIONS_H
