#include <catch.hpp>
#include "../types.h"
#include "../Swarm.h"
#include "../functions.h"
#include "../arrayhelpers.h"

using namespace MetaOpt;

TEST_CASE( "Swarm Setup", "[Swarm.Swarm]" ) {
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(-1, 1);

  REQUIRE_NOTHROW(Swarm sw(10, parameters, 50));
}

TEST_CASE("Swarm Optimize Parabola", "[Swarm.Optimize]") {
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(-1, 1);
  parameters["x1"] = std::make_pair(-1, 1);

  Swarm sw(10, parameters, 50);

  CostFunction func = parabola;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution.at("x0") == Approx(0).epsilon(0.01));
  REQUIRE(solution.at("x1") == Approx(0).epsilon(0.01));
}

TEST_CASE("Swarm Optimize Rosenbrock", "[Swarm.Optimize]") {
  ParameterSpace parameters;
  parameters["x0"] = std::make_pair(1.0, 5.0);
  parameters["x1"] = std::make_pair(1.0, 5.0);
  parameters["x2"] = std::make_pair(1.0, 5.0);

  Swarm sw(10, parameters, 50);

  CostFunction func = rosen;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestParameters();

  REQUIRE(func(solution) == Approx(1.321).epsilon(0.1));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution.at("x0") == Approx(1).epsilon(1));
  REQUIRE(solution.at("x1") == Approx(1).epsilon(1));
  REQUIRE(solution.at("x2") == Approx(1).epsilon(1));
}
