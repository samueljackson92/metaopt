#include "types.hpp"
#include "random_generator.hpp"
#include "simulated_annealing.h"

using namespace Optima;

SimulatedAnnealing::SimulatedAnnealing(const Parameters &parameters,
        const SimulatedAnnealingHyperParameters &hyperParams)
    : m_params(parameters), m_hyperParams(hyperParams) {
}

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

auto SimulatedAnnealing::acceptanceCriteria(double cost, double newCost, double temperature) -> double {
    if (newCost < cost) {
        return 1.0;
    } else {
        return std::exp(-(newCost - cost) / temperature);
    }
}
