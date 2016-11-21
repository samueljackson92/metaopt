#include "Particle.h"
#include "ArrayHelpers.h"

#include <Eigen/Core>

using namespace MetaOpt;
using namespace Eigen;

Particle::Particle(const ParameterSpace &paramSpace)
    : parameterSpace(paramSpace) {

  parameterNames.reserve(paramSpace.size());
  for (const auto &param : paramSpace) {
    parameterNames.push_back(param.first);
  }
  std::sort(parameterNames.begin(), parameterNames.end());

  const auto bounds = makeBoundsFromParameters(parameterSpace);
  const ArrayXd pos = ArrayHelpers::uniformFromBounds(bounds);
  initPosition(pos);
  initVelocity(bounds);
}

const Parameters &Particle::getParameters() {
  return getParametersFromArray(parameters, position);
}

const Parameters &Particle::getBestParameters() {
  return getParametersFromArray(bestParameters, bestPosition);
}

void Particle::initPosition(const ArrayXd &pos) {
  position = pos;
  bestPosition = pos;

  int index = 0;
  for (const auto &name : parameterNames) {
    parameters.emplace(name, pos(index));
    bestParameters.emplace(name, pos(index));
    ++index;
  }
}

void Particle::initVelocity(const Bounds &bounds) {
  const ArrayXd lower = bounds.first;
  const ArrayXd upper = bounds.second;
  const ArrayXd range = upper - lower;

  double v = range.matrix().norm();
  const ArrayXd vrange = ArrayXd::Constant(position.size(), -v);
  auto vbound = std::make_pair(-vrange, vrange);
  velocity = ArrayHelpers::uniformFromBounds(vbound);
}

Bounds
Particle::makeBoundsFromParameters(const ParameterSpace &parameters) const {
  auto nDims = parameters.size();
  ArrayXd lower(nDims);
  ArrayXd upper(nDims);

  int index = 0;
  for (const auto &name : parameterNames) {
    auto values = parameters.at(name);
    lower(index) = values.first;
    upper(index) = values.second;
    ++index;
  }

  return std::make_pair(lower, upper);
}

void Particle::setParametersFromArray(const ArrayXd &array,
                                      Parameters &params) {
  int index = 0;
  for (const auto &param : params) {
    auto name = param.first;
    auto value = array(index);
    params[name] = value;
    ++index;
  }
}

const Parameters &Particle::getParametersFromArray(Parameters &params,
                                                   const ArrayXd &array) {
  int index = 0;
  for (auto &name : parameterNames) {
    params[name] = array(index);
    ++index;
  }
  return params;
}
