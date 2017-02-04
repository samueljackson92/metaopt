#include <memory>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <tbb/tbb.h>
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

  auto bestParticle = findBestParticle(func);
  bestPosition = bestParticle->getPosition();
  bestParameters = bestParticle->getParameters();

  while (currentIteration < numIterations) {
      tbb::parallel_for(tbb::blocked_range<size_t>(0, 10),
        [this](const tbb::blocked_range<size_t> &r) {
            for (size_t i = r.begin(); i != r.end(); ++i) {
                auto particle = particles[i];
                updateParticle(particle);
                updateBestPositions(particle);
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

  ArrayXd rp = ArrayHelpers::randomArray(x.size());
  ArrayXd rg = ArrayHelpers::randomArray(x.size());

  ArrayXd bestPos;
  double phi_local, phi_global, omega;
  {
      // accquire shared data
      tbb::mutex::scoped_lock lock(particleUpdateMutex);
      phi_local = hyperParameters["phi_local"];
      phi_global = hyperParameters["phi_global"];
      omega = hyperParameters["omega"];
      bestPos = bestPosition;
  }

  // local & global contributions
  ArrayXd local_part = phi_local * rp * (p - x);
  ArrayXd global_part = phi_global * rg * (bestPosition - x);

  // update position & velocity
  v = omega * v + local_part + global_part;
  x += v;
}

void Swarm::updateBestPositions(const Particle_ptr particle)
{
  auto x = particle->getParameters();
  auto p = particle->getBestParameters();

  tbb::mutex::scoped_lock lock(particleUpdateMutex);
  auto value = func(x);
  auto bestValue = func(p);

  // check if this value was better than out personal best
  if (value >= bestValue)
      return;

  // update
  ArrayXd &pos = particle->getPosition();
  particle->setBestPosition(pos);

  // check is this is better than the global best
  auto globalBestValue = func(bestParameters);
  if (value >= globalBestValue)
      return;

  // update
  bestParameters = x;
  bestPosition = particle->getPosition();
}
