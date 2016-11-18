#include <catch.hpp>
#include "../Types.h"

#include "../Swarm.h"
#include "../Functions.h"
#include "../ArrayHelpers.h"

using namespace MetaOpt;

Parameters makeHyperParameters() {
  Parameters params;
  params["omega"] = 0.1;
  params["phi_local"] = 0.1;
  params["phi_global"] = 0.1;
  return params;
}

TEST_CASE( "Swarm Setup", "[Swarm.Swarm]" ) {
  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(-1, 1);

  REQUIRE_NOTHROW(Swarm sw(parameters, hyperParams, 10, 50));
}

TEST_CASE("Swarm Optimize Parabola", "[Swarm.Optimize]") {
  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);

  Swarm sw(parameters, hyperParams, 10, 50);

  CostFunction func = parabola;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution.at("x0") == Approx(0).epsilon(0.01));
  REQUIRE(solution.at("x1") == Approx(0).epsilon(0.01));
}

TEST_CASE("Swarm Optimize Rosenbrock", "[Swarm.Optimize]") {
  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-3, 3);
  parameters["x1"] = std::make_pair(-3, 3);
  parameters["x2"] = std::make_pair(-3, 3);

  Swarm sw(parameters, hyperParams, 10, 50);

  CostFunction func = rosen;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.01));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(1).epsilon(0.1));
  REQUIRE(solution.at("x1") == Approx(1).epsilon(0.1));
  REQUIRE(solution.at("x2") == Approx(1).epsilon(0.1));
}

TEST_CASE("Swarm Optimize HyperParams", "[Swarm.Optimize]") {
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

  Swarm sw(parameters, hyperParams, 10, 50);

  CostFunction func = rosen;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.0001));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(1).epsilon(0.001));
  REQUIRE(solution.at("x1") == Approx(1).epsilon(0.001));
  REQUIRE(solution.at("x2") == Approx(1).epsilon(0.001));
}

TEST_CASE("Swarm Optimize Iterations", "[Swarm.Optimize]") {
  Parameters hyperParams = makeHyperParameters();
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-3, 3);
  parameters["x1"] = std::make_pair(-3, 3);
  parameters["x2"] = std::make_pair(-3, 3);

  Swarm sw(parameters, hyperParams, 10, 50);

  CostFunction func = rosen;
  REQUIRE_NOTHROW(sw.optimize(func, 100));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(69.4).epsilon(0.1));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(-0.2).epsilon(0.1));
  REQUIRE(solution.at("x1") == Approx(0.6).epsilon(0.1));
  REQUIRE(solution.at("x2") == Approx(-0.1).epsilon(0.1));
}
