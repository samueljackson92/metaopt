#include <memory>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <tbb/parallel_for.h>
#include <iostream>

#include "particle.hpp"
#include "swarm.hpp"
#include "array_helpers.hpp"

using namespace Eigen;
using namespace Optima;

Swarm::Swarm(const ParameterSpace &parameters,
             const Parameters &hyperParameters, size_t num_particles)
    : num_particles(num_particles), hyperParameters(hyperParameters) {
  initParticles(parameters);
}

void Swarm::optimize(const CostFunction &func,
                     const std::size_t numIterations) {
  this->func = func;
  size_t currentIteration = 0;
  costs.reserve(numIterations);

  auto bestParticle = findBestParticle(func);
  bestPosition = bestParticle->getPosition();
  bestParameters = bestParticle->getParameters();

  const auto range = tbb::blocked_range<size_t>(0, particles.size());
  while (currentIteration < numIterations) {
    tbb::parallel_for(range, [this](const tbb::blocked_range<size_t>& r) {
        for (size_t i = r.begin(); i < r.end(); ++i) {
            updateParticle(particles[i]);
            updateBestPositions(particles[i]);
        }
    });
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
  ArrayXd &x = particle->getPosition();
  ArrayXd &p = particle->getBestPosition();
  ArrayXd &v = particle->getVelocity();

  const ArrayXd rp = ArrayHelpers::randomArray(x.size());
  const ArrayXd rg = ArrayHelpers::randomArray(x.size());

  const auto phi_local = hyperParameters["phi_local"];
  const auto phi_global = hyperParameters["phi_global"];
  const auto omega = hyperParameters["omega"];

  // local & global contributions
  ArrayXd local_part = phi_local * rp * (p - x);
  ArrayXd global_part = phi_global * rg * (bestPosition - x);

  // update position & velocity
  v = omega * v + local_part + global_part;
  x += v;
}

void Swarm::updateBestPositions(const Particle_ptr particle)
{
  const auto &x = particle->getParameters();
  const auto &p = particle->getBestParameters();

  const auto value = func(x);
  const auto bestValue = func(p);

  if (value >= bestValue)
      return;

  ArrayXd &pos = particle->getPosition();
  ArrayXd &bstPos = particle->getBestPosition();
  bstPos = pos;

  tbb::mutex::scoped_lock lock(updateMutex);
  costs.push_back(bestValue);

  auto globalBestValue = func(bestParameters);
  if (value < globalBestValue) {
      bestParameters = x;
      bestPosition = particle->getPosition();
  }
}
