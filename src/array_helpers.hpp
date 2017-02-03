#ifndef ARRAYHELPERS_H
#define ARRAYHELPERS_H

#include "random_generator.hpp"
#include "types.hpp"

#include <Eigen/Core>
#include <random>

namespace Optima
{

class ArrayHelpers {

public:
  static Eigen::ArrayXd randomArray(const size_t dimension) {
    auto randNum  = [](Eigen::DenseIndex& index) -> double {
      (void) index; // unused arg
      return RandomGenerator::uniform<double>();
    };
    return Eigen::ArrayXd::NullaryExpr(dimension, 1, randNum );
  }

  static Eigen::ArrayXd uniformFromBounds(const Bounds &bounds) {
    const Eigen::ArrayXd &lower = bounds.first;
    const Eigen::ArrayXd &upper = bounds.second;
    const Eigen::ArrayXd &range = upper - lower;
    const size_t dimension = lower.size();
    return ((randomArray(dimension) + 1) / 2) * range + lower;
  }

};
}

#endif // ARRAYHELPERS_H
