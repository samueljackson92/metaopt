#ifndef TYPES_H
#define TYPES_H

#include <utility>
#include <Eigen/Core>

/// Pair of vectors defining the bounds of the search space
typedef std::pair<Eigen::ArrayXd, Eigen::ArrayXd> Bounds;

#endif // TYPES_H
