#include "types.hpp"
#include "random_generator.hpp"
#include "simulated_annealing.hpp"

using namespace Optima;

SimulatedAnnealing::SimulatedAnnealing(const Parameters &parameters,
        const SimulatedAnnealingHyperParameters &hyperParams)
    : m_params(parameters), m_hyperParams(hyperParams) {
}

/**
 * Optimise the objective function for a given number of iterations
 *
 * @param func :: the objective cost function to optimise
 * @param numIterations :: the number of iterations to run
 */
void SimulatedAnnealing::optimize(const CostFunction &func,
                             const std::size_t numIterations) {

    m_bestCost  = func(m_params);
    auto temperature = m_hyperParams.initialTemp;
    for(size_t i = 0; i < numIterations; ++i) {
        temperature = m_hyperParams.temperatureFunc(temperature, i);
        auto newParams = m_hyperParams.neighbourFunc(m_params);
        auto newCost = func(newParams);

        auto randNum = RandomGenerator::uniform(0.0, 1.0);
        if(acceptanceCriteria(m_bestCost, newCost, temperature) >= randNum) {
            m_params = newParams;
            m_bestCost = newCost;
        }
    }
}

/**
 * Acceptance criteria function
 *
 * This is the same one as proposed by Kirkpatrick et al. A new cost which is
 * less than the old cost is always chosen. Otherwise it is chosen with
 * probability exp( -(e' - e) / t)
 *
 * @param cost :: the current best cost found
 * @param newCost :: the proposed new cost
 * @param temperature :: the current temperature of the system
 * @return double between 0-1 indicating the likelihood that the new cost is
 * chosen
 */
auto SimulatedAnnealing::acceptanceCriteria(double cost, double newCost, double temperature) -> double {
    if (newCost < cost) {
        return 1.0;
    } else {
        return std::exp(-(newCost - cost) / temperature);
    }
}
