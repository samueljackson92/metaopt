#include <cstddef>
#include <vector>
#include <Eigen/Core>

#include "Types.h"
#include "Particle.h"

namespace MetaOpt {
class Swarm {
public:
    Swarm(std::size_t num_particles, const Bounds& bounds, const int seed = -1);
    /// Optimize the cost function using the swarm
    void optimize(const CostFunction &func);
    /// Get the best soultion found
    Eigen::ArrayXd getBestSolution() const { return bestPosition; }

private:
    /// set the system random seed.
    void setRandomSeed(const int seed) const;
    /// initilise particles with random positions & velocity
    void initParticles(const Bounds& bounds);
    /// find the particle wiht the best candidate solution
    Particle_ptr findBestParticle(const CostFunction& func) const;

    /// Total number of particles in the swarm
    const std::size_t num_particles;
    /// Vector of particle objects in the swarm
    std::vector<Particle_ptr> particles;
    /// Current best position found by any member of the swarm
    Eigen::ArrayXd bestPosition;

};
}
