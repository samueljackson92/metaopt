#ifndef TYPES_H
#define TYPES_H

#include <Eigen/Core>
#include <functional>
#include <map>
#include <utility>

namespace MetaOpt {

/// Pair of vectors defining the bounds of the search space
typedef std::pair<Eigen::ArrayXd, Eigen::ArrayXd> Bounds;
/// Typedef for a parameter space
typedef std::map<std::string, std::pair<double, double>> ParameterSpace;
/// Typedef for a paramerter set
typedef std::map<std::string, double> Parameters;
/// Typedef for a cost function
typedef std::function<double(Parameters const &)> CostFunction;
}

#endif // TYPES_H
