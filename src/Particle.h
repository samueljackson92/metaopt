#ifndef PARTICLE_H
#define PARTICLE_H

#include <Eigen/Dense>
#include "Types.h"

namespace MetaOpt {

class Particle
{
public:
    Particle(const Bounds& bounds);

    /// Get the current position of the particle
    Eigen::ArrayXd getPosition() const { return position; }
    /// Get the current velocity of the particle
    Eigen::ArrayXd getVelocity() const { return velocity; }
    /// Get the best position found by this particle
    Eigen::ArrayXd getBestPosition() const { return bestPosition; }

    /// Set the current position of the particle
    void setPosition(const Eigen::ArrayXd& p) { position = p; }
    /// Set the current velocity of the particle
    void setVelocity(const Eigen::ArrayXd& v) { velocity = v; }
    /// Set the best position found by this particle
    void setBestPosition(const Eigen::ArrayXd& bp) { bestPosition = bp; }

private:
    /// Number of dimensions for the particle
    const size_t dimension;
    /// Current position of the particle
    Eigen::ArrayXd position;
    /// Current velocity of the particle
    Eigen::ArrayXd velocity;
    /// Best position found by the particle
    Eigen::ArrayXd bestPosition;
};

// export typedef of pointer type
typedef std::shared_ptr<Particle> Particle_ptr;

}

#endif // PARTICLE_H
