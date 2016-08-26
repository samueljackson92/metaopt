#ifndef ARRAYHELPERS_H
#define ARRAYHELPERS_H

#include "Types.h"
#include <Eigen/Core>

namespace MetaOpt
{

Bounds makeBounds(const size_t n, const double upper,
                          const double lower) {

  Eigen::ArrayXd upperBound = Eigen::ArrayXd::Constant(n, upper);
  Eigen::ArrayXd lowerBound = Eigen::ArrayXd::Constant(n, lower);
  return std::make_pair(lowerBound, upperBound);
}

Eigen::ArrayXd uniformFromBounds(const Bounds &bounds) {
  const Eigen::ArrayXd &lower = bounds.first;
  const Eigen::ArrayXd &upper = bounds.second;
  const Eigen::ArrayXd &range = upper - lower;
  const std::size_t dimension = lower.size();
  return ((Eigen::ArrayXd::Random(dimension) + 1) / 2) * range + lower;
}

}

#endif // ARRAYHELPERS_H
