#ifndef SIMULATEDANNEALING_H
#define SIMULATEDANNEALING_H

#include "types.hpp"

/**
 * Simulated Annealing optimiser
 *
 * This class proivides an implementation of the simulated annealing algorithm
 */


namespace Optima {

using namespace MetaOpt;

struct SimulatedAnnealingHyperParameters {
    std::function<double(double temperature, size_t iteration)> temperatureFunc;
    std::function<Parameters(const Parameters &params)> neighbourFunc;
    double initialTemp;
};

class SimulatedAnnealing {

public:
    /// Construct a new simulated annealing optimizer
    SimulatedAnnealing(const Parameters &parameters,
                       const SimulatedAnnealingHyperParameters &hyperParams);

    /// Optimize the cost function using the optimizer
    void optimize(const CostFunction &func,
                  const std::size_t numIterations = 1000);
    /// Get the best parameters found
    auto getBestParameters() const -> Parameters { return m_params; }
    /// Get the best solution found
    auto getBestSolution() const -> double { return m_bestCost; }


private:
    /// Acceptance criteria function
    auto acceptanceCriteria(double cost, double newCost, double temperature) -> double;

    double m_bestCost;
    SimulatedAnnealingHyperParameters m_hyperParams;
    Parameters m_params;
};
} // Optima

#endif
