#ifndef TYPES_H
#define TYPES_H

#include <utility>
#include <functional>
#include <Eigen/Core>

namespace MetaOpt {

/// Pair of vectors defining the bounds of the search space
typedef std::pair<Eigen::ArrayXd, Eigen::ArrayXd> Bounds;
/// Typedef for an cost function
typedef std::function<double(Eigen::ArrayXd const &)> CostFunction;
}

#endif // TYPES_H
