#include "ArrayHelpers.h"
#include "Particle.h"

#include <Eigen/Core>

using namespace MetaOpt;
using namespace Eigen;

Particle::Particle(const Bounds& bounds)
    : dimension(bounds.first.size())
{
    position = uniformFromBounds(bounds);
    bestPosition = position;

    const ArrayXd& lower = bounds.first;
    const ArrayXd& upper = bounds.second;
    const ArrayXd& range = upper - lower;

    double v = range.matrix().norm();
    const ArrayXd& vrange = ArrayXd::Constant(position.size(), -v);
    auto vbound = std::make_pair(-vrange, vrange);
    velocity = uniformFromBounds(vbound);
}
