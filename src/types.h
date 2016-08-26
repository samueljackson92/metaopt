#ifndef TYPES_H
#define TYPES_H

#include <utility>
#include <functional>
#include <Eigen/Core>

/// Pair of vectors defining the bounds of the search space
typedef std::pair<Eigen::ArrayXd, Eigen::ArrayXd> Bounds;
/// Typedef for an cost function
typedef std::function<double(const Eigen::ArrayXd&)> CostFunction;

#endif // TYPES_H
