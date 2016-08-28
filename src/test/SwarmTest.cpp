#include <catch.hpp>
#include "../types.h"
#include "../Swarm.h"
#include "../functions.h"
#include "../arrayhelpers.h"

using namespace MetaOpt;

TEST_CASE( "Swarm Setup", "[Swarm.Swarm]" ) {
    auto bounds = makeBounds(3, 1, 5);
    REQUIRE_NOTHROW( Swarm sw(10, bounds, 50) );
}

TEST_CASE("Swarm Optimize Parabola", "[Swarm.Optimize]") {
  auto bounds = makeBounds(2, -1, 1);
  Swarm sw(10, bounds, 50);

  CostFunction func = parabola;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestSolution();

  REQUIRE(func(solution) == Approx(0).epsilon(0.001));
  REQUIRE(solution.size() == 2);
  REQUIRE(solution(0) == Approx(0).epsilon(0.001));
  REQUIRE(solution(1) == Approx(0).epsilon(0.001));
}

TEST_CASE("Swarm Optimize Rosenbrock", "[Swarm.Optimize]") {
  auto bounds = makeBounds(3, 1, 5);
  Swarm sw(10, bounds, 50);

  CostFunction func = rosen;
  REQUIRE_NOTHROW(sw.optimize(func));
  auto solution = sw.getBestSolution();

  REQUIRE(func(solution) == Approx(181.646).epsilon(0.001));
  REQUIRE(solution.size() == 3);
  REQUIRE(solution(0) == Approx(1.805).epsilon(0.001));
  REQUIRE(solution(1) == Approx(1.960).epsilon(0.001));
  REQUIRE(solution(2) == Approx(3.503).epsilon(0.001));
}
