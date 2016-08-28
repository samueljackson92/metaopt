#include <memory>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "Particle.h"
#include "Swarm.h"

using namespace Eigen;
using namespace MetaOpt;

Swarm::Swarm(size_t num_particles, const ParameterSpace &parameters,
             const int seed)
    : num_particles(num_particles) {
  SwarmHyperParameters params;
  params.omega = 0.1;
  params.phi_local = 0.1;
  params.phi_global = 0.1;

  this->params = params;
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

    // local & global contributions
    ArrayXd local_part = params.phi_local * rp * (p - x);
    ArrayXd global_part = params.phi_global * rg * (bestPosition - x);

    // update position
    v = params.omega * v + local_part + global_part;
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
    particle->setBestPosition(particle->getBestPosition());

    auto globalBestValue = func(bestParameters);
    if (value < globalBestValue) {
      bestParameters = x;
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
