#include <cstddef>
#include <vector>
#include <Eigen/Core>

#include "Types.h"
#include "Particle.h"

namespace MetaOpt {
class Swarm {
public:
    Swarm(std::size_t num_particles, const Bounds& bounds, const int seed = -1);
    /// set the system random seed.
    void setRandomSeed(const int seed) const;
    /// initilise particles with random positions & velocity
    void initParticles(const Bounds& bounds);

private:
    const std::size_t num_particles;
    std::vector<Particle_ptr> particles;
};
}
