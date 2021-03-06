#include <catch.hpp>

#include "../types.hpp"
#include "../functions.hpp"
#include "../random_generator.hpp"
#include "../simulated_annealing.hpp"

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
  auto solution = annealer.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution.at("x0") == Approx(0).epsilon(0.01));
  REQUIRE(solution.at("x1") == Approx(0).epsilon(0.01));
}

TEST_CASE( "SimulatedAnnealing Optimize Rosen", "[SimulatedAnnealing.Optimize]" ) {
  RandomGenerator::seed(50);

  // setup parameters
  Parameters params;
  params["x0"] = RandomGenerator::uniform(-10., 10.);
  params["x1"] = RandomGenerator::uniform(-10., 10.);
  params["x2"] = RandomGenerator::uniform(-10., 10.);

  // setup hyper parameters
  SimulatedAnnealingHyperParameters hyperParams;
  hyperParams.initialTemp = 100000.0;

  hyperParams.temperatureFunc = [](double temperature, size_t iteration) -> double {
    return temperature/std::log(static_cast<double>(iteration+2));
  };

  hyperParams.neighbourFunc = [](const Parameters& params) -> Parameters {
      auto newParams = params;
      newParams["x0"] += RandomGenerator::uniform(-1., 1.);
      newParams["x1"] += RandomGenerator::uniform(-1., 1.);
      newParams["x2"] += RandomGenerator::uniform(-1., 1.);
      return newParams;
  };

  CostFunction func = TestFunctions::rosen;

  // Optimize objective function
  SimulatedAnnealing annealer(params, hyperParams);
  REQUIRE_NOTHROW(annealer.optimize(func, 100000));
  auto solution = annealer.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.03));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(1.).epsilon(0.05));
  REQUIRE(solution.at("x1") == Approx(1.).epsilon(0.05));
  REQUIRE(solution.at("x2") == Approx(1.).epsilon(0.05));
}
