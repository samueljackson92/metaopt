#include <memory>
#include <stdlib.h>
#include <time.h>
#include <random>

#include "Particle.h"
#include "Swarm.h"

using namespace Eigen;
using namespace MetaOpt;

Swarm::Swarm(size_t num_particles, const Parameters &parameters, const int seed)
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

    while (currentIteration < iterations) {
        for (auto particle : particles) {
            updateParticle(particle);
            updateBestPositions(particle);
        }
        ++currentIteration;
    }
}

void Swarm::initParticles(const Parameters &parameters) {
  Bounds bounds = makeBoundsFromParameters(parameters);
  particles.reserve(num_particles);
  for (size_t i = 0; i < num_particles; ++i) {
    auto particle = std::make_shared<Particle>(bounds);
    particles.push_back(particle);
  }
}

Particle_ptr Swarm::findBestParticle(const CostFunction &func) const
{
    auto comp = [&func](const Particle_ptr p1, const Particle_ptr p2) {
       return func(p1->getPosition()) < func(p2->getPosition());
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
    ArrayXd x = particle->getPosition();
    ArrayXd p = particle->getBestPosition();

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

void Swarm::setRandomSeed(const int seed) const {
  if (seed > 0) {
    srand(seed);
  } else {
    srand(time(NULL));
  }
}

Bounds Swarm::makeBoundsFromParameters(const Parameters &parameters) const {
  auto nDims = parameters.size();
  ArrayXd lower(nDims);
  ArrayXd upper(nDims);

  int index = 0;
  for (const auto &param : parameters) {
    auto values = param.second;
    lower(index) = values.first;
    upper(index) = values.second;
    ++index;
  }

  return std::make_pair(lower, upper);
}
