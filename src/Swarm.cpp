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

void Swarm::optimize(const CostFunction &func)
{
    auto bestParticle = findBestParticle(func);
    bestPosition = bestParticle->getPosition();
}

void Swarm::initParticles(const Bounds &bounds) {
  particles.reserve(num_particles);
  for (size_t i = 0; i < num_particles; ++i) {
    auto particle = std::make_shared<Particle>(bounds);
    particles.push_back(particle);
  }
}

Particle_ptr Swarm::findBestParticle(const CostFunction &func) const
{
    const auto elem = std::min_element(particles.begin(), particles.end(),
                                 [&func](const Particle_ptr p1, const Particle_ptr p2) {
       return func(p1->getPosition()) < func(p2->getPosition());
    });

    return *elem;
}

void Swarm::setRandomSeed(const int seed) const {
  if (seed > 0) {
    srand(seed);
  } else {
    srand(time(NULL));
  }
}
