#include <memory>
#include <stdlib.h>
#include <time.h>

#include "Particle.h"
#include "Swarm.h"

using namespace Eigen;
using namespace MetaOpt;

Swarm::Swarm(size_t num_particles, const Bounds &bounds, const int seed)
    : num_particles(num_particles) {
  setRandomSeed(seed);
  initParticles(bounds);
}

void Swarm::initParticles(const Bounds &bounds) {
  particles.reserve(num_particles);
  for (size_t i = 0; i < num_particles; ++i) {
    auto particle = std::make_shared<Particle>(bounds);
    particles.push_back(particle);
  }
}

void Swarm::setRandomSeed(const int seed) const {
  if (seed > 0) {
    srand(seed);
  } else {
    srand(time(NULL));
  }
}
