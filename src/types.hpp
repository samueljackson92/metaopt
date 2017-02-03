#ifndef TYPES_H
#define TYPES_H

#include <Eigen/Core>
#include <functional>
#include <unordered_map>
#include <utility>

namespace Optima {

/// Pair of vectors defining the bounds of the search space
typedef std::pair<Eigen::ArrayXd, Eigen::ArrayXd> Bounds;
/// Typedef for a parameter space
typedef std::unordered_map<std::string, std::pair<double, double>>
    ParameterSpace;
/// Typedef for a paramerter set
typedef std::unordered_map<std::string, double> Parameters;
/// Typedef for a cost function
typedef std::function<double(Parameters const &)> CostFunction;

}

#endif // TYPES_H
