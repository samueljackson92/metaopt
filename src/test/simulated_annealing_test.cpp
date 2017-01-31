#include <catch.hpp>

#include "../Types.h"
#include "../Functions.h"
#include "../RandomGenerator.hpp"
#include "../simulated_annealing.h"

using namespace MetaOpt;
using namespace Optima;

TEST_CASE( "SimulatedAnnealing Optimize Parabola", "[SimulatedAnnealing.Optimize]" ) {
  RandomGenerator::seed(50);

  // setup parameters
  Parameters params;
  params["x0"] = RandomGenerator::uniform(-10., 10.);
  params["x1"] = RandomGenerator::uniform(-10., 10.);

  // setup hyper parameters
  SimulatedAnnealingHyperParameters hyperParams;
  hyperParams.initialTemp = 10000.0;

  hyperParams.temperatureFunc = [](double temperature, size_t iteration) -> double {
    return temperature/std::log(static_cast<double>(iteration+2));
  };

  hyperParams.neighbourFunc = [](const Parameters& params) -> Parameters {
      auto newParams = params;
      newParams["x0"] += RandomGenerator::uniform(-1., 1.);
      newParams["x1"] += RandomGenerator::uniform(-1., 1.);
      return newParams;
  };

  CostFunction func = TestFunctions::parabola;

  // Optimize objective function
  SimulatedAnnealing annealer(params, hyperParams);
  REQUIRE_NOTHROW(annealer.optimize(func, 10000));
  auto solution = annealer.getParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution.at("x0") == Approx(0).epsilon(0.01));
  REQUIRE(solution.at("x1") == Approx(0).epsilon(0.01));
}

