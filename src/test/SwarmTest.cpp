#include <catch.hpp>
#include "../types.h"
#include "../Swarm.h"
#include "../functions.h"
#include "../arrayhelpers.h"

using namespace MetaOpt;

TEST_CASE( "Swarm Setup", "[Swarm.Swarm]" ) {
  Parameters parameters;
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(-1, 1);
  parameters["x3"] = std::make_pair(-1, 1);

  REQUIRE_NOTHROW(Swarm sw(10, parameters, 50));
}

TEST_CASE("Swarm Optimize Parabola", "[Swarm.Optimize]") {
  Parameters parameters;
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(-1, 1);

  Swarm sw(10, parameters, 50);

  CostFunction func = parabola;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestSolution();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution(0) == Approx(0).epsilon(0.001));
  REQUIRE(solution(1) == Approx(0).epsilon(0.001));
}

TEST_CASE("Swarm Optimize Rosenbrock", "[Swarm.Optimize]") {
  Parameters parameters;
  parameters["x1"] = std::make_pair(1.0, 5.0);
  parameters["x2"] = std::make_pair(1.0, 5.0);
  parameters["x3"] = std::make_pair(1.0, 5.0);

  Swarm sw(10, parameters, 50);

  CostFunction func = rosen;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestSolution();

  REQUIRE(func(solution) == Approx(2.090).epsilon(0.001));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution(0) == Approx(1.524).epsilon(0.001));
  REQUIRE(solution(1) == Approx(2.283).epsilon(0.001));
  REQUIRE(solution(2) == Approx(5.209).epsilon(0.001));
}
