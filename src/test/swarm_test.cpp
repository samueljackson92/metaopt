#include <catch.hpp>
#include "../types.hpp"

#include "../swarm.hpp"
#include "../functions.hpp"
#include "../array_helpers.hpp"

using namespace Optima;

Parameters makeHyperParameters() {
  Parameters params;
  params["omega"] = 0.1;
  params["phi_local"] = 0.1;
  params["phi_global"] = 0.1;
  return params;
}

TEST_CASE( "Swarm Setup", "[Swarm.Swarm]" ) {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(-1, 1);

  REQUIRE_NOTHROW(Swarm sw(parameters, hyperParams, 10));
}

TEST_CASE("Swarm Optimize Parabola", "[Swarm.Optimize]") {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);

  Swarm sw(parameters, hyperParams, 10);

  CostFunction func = TestFunctions::parabola;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution.at("x0") == Approx(0).epsilon(0.01));
  REQUIRE(solution.at("x1") == Approx(0).epsilon(0.01));
}

TEST_CASE("Swarm Optimize Rosenbrock", "[Swarm.Optimize]") {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  hyperParams["omega"] = 0.5;
  hyperParams["phi_local"] = 0.5;
  hyperParams["phi_global"] = 0.5;

  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-3, 3);
  parameters["x1"] = std::make_pair(-3, 3);
  parameters["x2"] = std::make_pair(-3, 3);

  Swarm sw(parameters, hyperParams, 10);

  CostFunction func = TestFunctions::rosen;
  REQUIRE_NOTHROW(sw.optimize(func, 10000));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.01));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(1).epsilon(0.1));
  REQUIRE(solution.at("x1") == Approx(1).epsilon(0.1));
  REQUIRE(solution.at("x2") == Approx(1).epsilon(0.1));
}

TEST_CASE("Swarm Optimize HyperParams", "[Swarm.Optimize]") {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  // A larger Omega parameter leads to faster convergence on the
  // correct parameter setting (1, 1, 1)
  hyperParams["omega"] = 0.5;
  hyperParams["phi_local"] = 0.1;
  hyperParams["phi_global"] = 0.1;

  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-3, 3);
  parameters["x1"] = std::make_pair(-3, 3);
  parameters["x2"] = std::make_pair(-3, 3);

  Swarm sw(parameters, hyperParams, 10);

  CostFunction func = TestFunctions::rosen;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.03));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(0.94).epsilon(0.1));
  REQUIRE(solution.at("x1") == Approx(1.04).epsilon(0.01));
  REQUIRE(solution.at("x2") == Approx(1.08).epsilon(0.01));
}

TEST_CASE("Swarm Optimize Iterations", "[Swarm.Optimize]") {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-3, 3);
  parameters["x1"] = std::make_pair(-3, 3);
  parameters["x2"] = std::make_pair(-3, 3);

  Swarm sw(parameters, hyperParams, 10);

  CostFunction func = TestFunctions::rosen;
  REQUIRE_NOTHROW(sw.optimize(func, 100));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(17.7).epsilon(0.1));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(-0.53).epsilon(0.1));
  REQUIRE(solution.at("x1") == Approx(0.05).epsilon(0.1));
  REQUIRE(solution.at("x2") == Approx(0.30).epsilon(0.1));
}
