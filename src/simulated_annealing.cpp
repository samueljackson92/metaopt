#include "Types.h"
#include "RandomGenerator.hpp"
#include "simulated_annealing.h"

using namespace Optima;
using namespace MetaOpt;

SimulatedAnnealing::SimulatedAnnealing(const Parameters &parameters,
        const SimulatedAnnealingHyperParameters &hyperParams)
    : m_params(parameters), m_hyperParams(hyperParams) {
}

void SimulatedAnnealing::optimize(const CostFunction &func,
                             const std::size_t numIterations) {

    auto cost  = func(m_params);
    auto temperature = m_hyperParams.initialTemp;
    for(size_t i = 0; i < numIterations; ++i) {
        temperature = m_hyperParams.temperatureFunc(temperature, i);
        auto newParams = m_hyperParams.neighbourFunc(m_params);
        auto newCost = func(newParams);

        auto randNum = RandomGenerator::uniform(0.0, 1.0);
        if(acceptanceCriteria(cost, newCost, temperature) >= randNum) {
            m_params = newParams;
            cost = newCost;
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
