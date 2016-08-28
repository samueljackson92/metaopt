#ifndef PARTICLE_H
#define PARTICLE_H

#include <Eigen/Dense>
#include "Types.h"

namespace MetaOpt {

class Particle
{
public:
  Particle(const ParameterSpace &bounds);

  /// Get the current position of the particle
  Eigen::ArrayXd getPosition() const { return position; }
  /// Get the current velocity of the particle
  Eigen::ArrayXd getVelocity() const { return velocity; }
  /// Get the best position found by this particle
  Eigen::ArrayXd getBestPosition() const { return bestPosition; }
  /// Get the parameters for this particle
  Parameters getParameters() const { return parameters; }
  /// Get the best parameters found by this particle
  Parameters getBestParameters() const { return bestParameters; }

  /// Set the current position of the particle
  void setPosition(const Eigen::ArrayXd &p);
  /// Set the best position found by this particle
  void setBestPosition(const Eigen::ArrayXd &bp);
  /// Set the current velocity of the particle
  void setVelocity(const Eigen::ArrayXd &v) { velocity = v; }

private:
  /// Initilise the position of this particle
  void initPosition(const Eigen::ArrayXd &position);
  /// Initilise the velocity of this particle
  void initVelocity(const Bounds &bounds);
  /// Make space bounds from parameter map
  Bounds makeBoundsFromParameters(const ParameterSpace &parameters) const;
  /// Make parameter map from an array
  void setParametersFromArray(const Eigen::ArrayXd &array, Parameters &params);

  /// Current position of the particle
  Eigen::ArrayXd position;
  /// Current velocity of the particle
  Eigen::ArrayXd velocity;
  /// Best position found by the particle
  Eigen::ArrayXd bestPosition;
  /// The parameter map for the current position
  Parameters parameters;
  /// The parameter map for the best position found
  Parameters bestParameters;
  /// The parameter space for the particle
  const ParameterSpace parameterSpace;
};

// export typedef of pointer type
typedef std::shared_ptr<Particle> Particle_ptr;

}

#endif // PARTICLE_H
