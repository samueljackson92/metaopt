#include <catch.hpp>
#include <stdlib.h>
#include "../Particle.h"

using namespace MetaOpt;

TEST_CASE("Particle Setup", "[Particle]") {
  // seed the random number generator for Eigen
  srand(50);

  ParameterSpace parameters;
  parameters["x1"] = std::make_pair(1, 5);
  parameters["x2"] = std::make_pair(1, 5);
  parameters["x3"] = std::make_pair(1, 5);

  Particle p(parameters);
  Eigen::ArrayXd pos = p.getPosition();
  Eigen::ArrayXd bstPos = p.getBestPosition();
  Eigen::ArrayXd vel = p.getVelocity();

  REQUIRE(pos(0) == Approx(1.003).epsilon(0.001));
  REQUIRE(pos(1) == Approx(3.307).epsilon(0.001));
  REQUIRE(pos(2) == Approx(4.121).epsilon(0.001));

  REQUIRE(bstPos(0) == Approx(1.003).epsilon(0.001));
  REQUIRE(bstPos(1) == Approx(3.307).epsilon(0.001));
  REQUIRE(bstPos(2) == Approx(4.121).epsilon(0.001));

  REQUIRE(vel(0) == Approx(-5.99).epsilon(0.001));
  REQUIRE(vel(1) == Approx(-1.917).epsilon(0.001));
  REQUIRE(vel(2) == Approx(-6.207).epsilon(0.001));
}
