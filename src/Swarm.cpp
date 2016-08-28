#include <memory>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "Particle.h"
#include "Swarm.h"

using namespace Eigen;
using namespace MetaOpt;

Swarm::Swarm(const ParameterSpace &parameters,
             const Parameters &hyperParameters, size_t num_particles,
             const int seed)
    : num_particles(num_particles), hyperParameters(hyperParameters) {
  setRandomSeed(seed);
  initParticles(parameters);
}

void Swarm::optimize(const CostFunction &func)
{
    this->func = func;
    size_t iterations = 10000;
    size_t currentIteration = 0;

    auto bestParticle = findBestParticle(func);
    bestPosition = bestParticle->getPosition();
    bestParameters = bestParticle->getParameters();

    while (currentIteration < iterations) {
        for (auto particle : particles) {
            updateParticle(particle);
            updateBestPositions(particle);
        }
        ++currentIteration;
    }
}

void Swarm::initParticles(const ParameterSpace &parameters) {
  particles.reserve(num_particles);
  for (size_t i = 0; i < num_particles; ++i) {
    auto particle = std::make_shared<Particle>(parameters);
    particles.push_back(particle);
  }
}

Particle_ptr Swarm::findBestParticle(const CostFunction &func) const
{
  auto comp = [&func](const Particle_ptr p1, const Particle_ptr p2) {
    return func(p1->getParameters()) < func(p2->getParameters());
  };
  auto elem = std::min_element(particles.begin(), particles.end(), comp);
  return *elem;
}

void Swarm::updateParticle(const Particle_ptr particle)
{
    ArrayXd x = particle->getPosition();
    ArrayXd p = particle->getBestPosition();
    ArrayXd v = particle->getVelocity();

    ArrayXd rp = ArrayXd::Random(x.size());
    ArrayXd rg = ArrayXd::Random(x.size());

    double phi_local = hyperParameters["phi_local"];
    double phi_global = hyperParameters["phi_global"];
    double omega = hyperParameters["omega"];

    // local & global contributions
    ArrayXd local_part = phi_local * rp * (p - x);
    ArrayXd global_part = phi_global * rg * (bestPosition - x);

    // update position
    v = omega * v + local_part + global_part;
    x = x + v;
    particle->setVelocity(v);
    particle->setPosition(x);
}

void Swarm::updateBestPositions(const Particle_ptr particle)
{
  auto x = particle->getParameters();
  auto p = particle->getBestParameters();

  auto value = func(x);
  auto bestValue = func(p);

  if (value < bestValue) {
    particle->setBestPosition(particle->getPosition());

    auto globalBestValue = func(bestParameters);
    if (value < globalBestValue) {
      bestParameters = x;
      bestPosition = particle->getPosition();
    }
    }
}

void Swarm::setRandomSeed(const int seed) const {
  if (seed > 0) {
    srand(seed);
  } else {
    srand(time(NULL));
  }
}
