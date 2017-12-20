#ifndef SWARM_H
#define SWARM_H

#include <cstddef>
#include <vector>
#include <Eigen/Core>
#include <tbb/mutex.h>

#include "types.hpp"
#include "particle.hpp"

namespace Optima {

struct SwarmHyperParameters {
    double omega;
    double phi_local;
    double phi_global;
};

class Swarm {
public:
  Swarm(const ParameterSpace &parameters, const Parameters &hyperParameters,
        std::size_t num_particles = 10);
  /// Optimize the cost function using the swarm
  void optimize(const CostFunction &func,
                const std::size_t numIterations = 10000);
  /// Get the best soultion found
  Eigen::ArrayXd getBestSolution() const { return bestPosition; }
  Parameters getBestParameters() const { return bestParameters; }
  std::vector<double> getCosts() const { return costs; }

private:
    /// initilise particles with random positions & velocity
    void initParticles(const ParameterSpace &parameters);
    /// find the particle wiht the best candidate solution
    Particle_ptr findBestParticle(const CostFunction& func) const;
    /// update position & velocity of each particle
    void updateParticle(const Particle_ptr particle);
    /// update best local/global positions if necessary
    void updateBestPositions(const Particle_ptr particle);

    /// Total number of particles in the swarm
    const std::size_t num_particles;
    /// Vector of particle objects in the swarm
    std::vector<Particle_ptr> particles;
    /// Current best position found by any member of the swarm
    Eigen::ArrayXd bestPosition;
    /// Current best parameters found by any member of the swarm
    Parameters bestParameters;
    /// Hyper parameters for the swarm
    Parameters hyperParameters;
    /// Cost function
    CostFunction func;
    /// Global update mutex. Locks updates to the global best position
    tbb::mutex updateMutex;
    /// variable to store costs
    std::vector<double> costs;

};
}

#endif
