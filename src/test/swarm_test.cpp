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
  REQUIRE(solution.at("x0") == Approx(0).epsilon(0.1));
  REQUIRE(solution.at("x1") == Approx(0).epsilon(0.1));
}

TEST_CASE("Swarm Optimize Ackley", "[Swarm.Optimize]") {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-40, 40);
  parameters["x1"] = std::make_pair(-40, 40);
  parameters["x2"] = std::make_pair(-40, 40);

  Swarm sw(parameters, hyperParams, 10);

  CostFunction func = TestFunctions::ackley;
  REQUIRE_NOTHROW(sw.optimize(func, 100000));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(1.718).epsilon(1e-3));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(0.0).epsilon(.9));
  REQUIRE(solution.at("x1") == Approx(0.0).epsilon(.9));
  REQUIRE(solution.at("x2") == Approx(0.0).epsilon(.9));
}

TEST_CASE("Swarm Optimize Rosen", "[Swarm.Optimize]") {
  RandomGenerator::seed(50);

  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-40, 40);
  parameters["x1"] = std::make_pair(-40, 40);
  parameters["x2"] = std::make_pair(-40, 40);

  Swarm sw(parameters, hyperParams, 30);

  CostFunction func = TestFunctions::rosen;
  REQUIRE_NOTHROW(sw.optimize(func, 100000));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0.).epsilon(.5));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(0.0).epsilon(.9));
  REQUIRE(solution.at("x1") == Approx(0.0).epsilon(.9));
  REQUIRE(solution.at("x2") == Approx(0.0).epsilon(.9));
}
