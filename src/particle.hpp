#ifndef PARTICLE_H
#define PARTICLE_H

#include "types.hpp"

#include <Eigen/Dense>
#include <memory>
#include <vector>

namespace MetaOpt {

class Particle
{
public:
  Particle(const ParameterSpace &bounds);

  /// Get the current position of the particle
  Eigen::ArrayXd &getPosition() { return position; }
  /// Get the best position found by this particle
  Eigen::ArrayXd &getBestPosition() { return bestPosition; }
  /// Get the current velocity of the particle
  Eigen::ArrayXd &getVelocity() { return velocity; }
  /// Get the parameters for this particle
  const Parameters &getParameters();
  /// Get the best parameters found by this particle
  const Parameters &getBestParameters();

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
  /// Get parameter map from vector
  const Parameters &getParametersFromArray(Parameters &params,
                                           const Eigen::ArrayXd &array);

  /// Current position of the particle
  Eigen::ArrayXd position;
  /// Current velocity of the particle
  Eigen::ArrayXd velocity;
  /// Best position found by the particle
  Eigen::ArrayXd bestPosition;
  /// The parameter space for the particle
  const ParameterSpace parameterSpace;
  /// The parameters for this particle
  Parameters parameters;
  /// The best paramters found for this particle
  Parameters bestParameters;
  /// Names of the parameters for the ordered conversion
  std::vector<std::string> parameterNames;
};

// export typedef of pointer type
typedef std::shared_ptr<Particle> Particle_ptr;

}

#endif // PARTICLE_H
