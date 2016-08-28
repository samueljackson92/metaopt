#include "ArrayHelpers.h"
#include "Particle.h"

#include <Eigen/Core>

using namespace MetaOpt;
using namespace Eigen;

Particle::Particle(const ParameterSpace &paramSpace)
    : parameterSpace(paramSpace) {
  const auto bounds = makeBoundsFromParameters(parameterSpace);
  const ArrayXd pos = uniformFromBounds(bounds);
  initPosition(pos);
  initVelocity(bounds);
}

void Particle::setPosition(const ArrayXd &position) {
  this->position = position;
  setParametersFromArray(position, parameters);
}

void Particle::setBestPosition(const ArrayXd &position) {
  bestPosition = position;
  setParametersFromArray(position, bestParameters);
}

void Particle::initPosition(const ArrayXd &pos) {
  position = pos;
  bestPosition = pos;

  int index = 0;
  for (const auto &param : parameterSpace) {
    parameters.emplace(param.first, pos(index));
    bestParameters.emplace(param.first, pos(index));
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
  const ArrayXd vel = uniformFromBounds(vbound);
  setVelocity(vel);
}

Bounds
Particle::makeBoundsFromParameters(const ParameterSpace &parameters) const {
  auto nDims = parameters.size();
  ArrayXd lower(nDims);
  ArrayXd upper(nDims);

  int index = 0;
  for (const auto &param : parameters) {
    auto values = param.second;
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
