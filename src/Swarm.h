#include <cstddef>
#include <vector>
#include <Eigen/Core>

#include "Types.h"
#include "Particle.h"

namespace MetaOpt {

struct SwarmHyperParameters {
    double omega;
    double phi_local;
    double phi_global;
};

class Swarm {
public:
  Swarm(std::size_t num_particles, const Parameters &parameters,
        const int seed = -1);
  /// Optimize the cost function using the swarm
  void optimize(const CostFunction &func);
  /// Get the best soultion found
  Eigen::ArrayXd getBestSolution() const { return bestPosition; }

private:
    /// set the system random seed.
    void setRandomSeed(const int seed) const;
    /// Make space bounds from parameter map
    Bounds makeBoundsFromParameters(const Parameters &parameters) const;
    /// initilise particles with random positions & velocity
    void initParticles(const Parameters &parameters);
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
    /// Hyper parameters for the swarm
    SwarmHyperParameters params;
    /// Cost function
    CostFunction func;

};
}
