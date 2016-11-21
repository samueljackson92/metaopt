#ifndef ARRAYHELPERS_H
#define ARRAYHELPERS_H

#include "RandomGenerator.hpp"
#include "Types.h"

#include <Eigen/Core>
#include <random>

namespace MetaOpt
{

class ArrayHelpers {

public:
  static Eigen::ArrayXd randomArray(const size_t dimension) {
    auto randNum  = [&] () {return RandomGenerator::uniform<double>(); };
    return Eigen::ArrayXd::NullaryExpr(dimension, randNum );
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
