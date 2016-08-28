#ifndef ARRAYHELPERS_H
#define ARRAYHELPERS_H

#include "Types.h"
#include <Eigen/Core>

namespace MetaOpt
{

Eigen::ArrayXd uniformFromBounds(const Bounds &bounds) {
  const Eigen::ArrayXd &lower = bounds.first;
  const Eigen::ArrayXd &upper = bounds.second;
  const Eigen::ArrayXd &range = upper - lower;
  const std::size_t dimension = lower.size();
  return ((Eigen::ArrayXd::Random(dimension) + 1) / 2) * range + lower;
}

}

#endif // ARRAYHELPERS_H
