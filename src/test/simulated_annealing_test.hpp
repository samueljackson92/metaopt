#include <catch.hpp>
#include "../Types.h"
#include "../RandomGenerator.hpp"
#include "../Functions.h"
#include "../simulated_annealing.h"

using namespace Optima;
using namespace MetaOpt;

TEST_CASE( "Simulated Annealing Setup", "[SimulatedAnnealing.SimulatedAnnealing]" ) {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(-1, 1);

  SimulatedAnnealingHyperParameters hyperParams;
  hyperParams.temperatureFunc;

  REQUIRE_NOTHROW(Swarm sw(parameters, hyperParams, 10));
}
