#include <memory>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "Particle.h"
#include "Swarm.h"

using namespace Eigen;
using namespace MetaOpt;

struct SwarmHyperParameters {
    double omega;
    double phi_local;
    double phi_global;
};

Swarm::Swarm(size_t num_particles, const Bounds &bounds, const int seed)
    : num_particles(num_particles) {
  setRandomSeed(seed);
  initParticles(bounds);
}

void Swarm::optimize(const CostFunction &func)
{
    size_t iterations = 10000;
    size_t currentIteration = 0;

    auto bestParticle = findBestParticle(func);
    bestPosition = bestParticle->getPosition();

    while (currentIteration < iterations) {
        for (auto particle : particles) {

            SwarmHyperParameters params;
            params.omega = 0.1;
            params.phi_local = 0.1;
            params.phi_global = 0.1;

            ArrayXd x = particle->getPosition();
            ArrayXd p = particle->getBestPosition();
            ArrayXd v = particle->getVelocity();

            ArrayXd rp = ArrayXd::Random(x.size());
            ArrayXd rg = ArrayXd::Random(x.size());

            ArrayXd local_part = params.phi_local * rp * (p - x);
            ArrayXd global_part = params.phi_global * rg * (bestPosition - x);

            // update position
            v = params.omega * v + local_part + global_part;
            x = x + v;
            particle->setVelocity(v);
            particle->setPosition(x);

            auto value = func(x);
            auto bestValue = func(p);

            if (value < bestValue) {
                particle->setBestPosition(x);

                auto globalBestValue = func(bestPosition);
                if (value < globalBestValue) {
                    bestPosition = x;
                }
            }
        }
        ++currentIteration;
    }
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
