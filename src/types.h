#ifndef TYPES_H
#define TYPES_H

#include <Eigen/Core>
#include <functional>
#include <unordered_map>
#include <utility>

namespace MetaOpt {

/// Pair of vectors defining the bounds of the search space
typedef std::pair<Eigen::ArrayXd, Eigen::ArrayXd> Bounds;
/// Typedef for a cost function
typedef std::function<double(Eigen::ArrayXd const &)> CostFunction;
/// Typedef for a parameter set
typedef std::unordered_map<std::string, std::pair<double, double>> Parameters;
}

#endif // TYPES_H
