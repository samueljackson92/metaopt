#include <catch.hpp>
#include <stdlib.h>

#include "../random_generator.hpp"
#include "../particle.hpp"

using namespace Optima;

TEST_CASE("Particle Setup", "[Particle]") {
  // seed the random number generator for Eigen
  RandomGenerator::seed(50);
  ParameterSpace parameters;
  parameters["x1"] = std::make_pair(1, 5);
  parameters["x2"] = std::make_pair(1, 5);
  parameters["x3"] = std::make_pair(1, 5);

  Particle p(parameters);

  Eigen::ArrayXd pos = p.getPosition();
  REQUIRE(pos.size() == 3);
  REQUIRE(pos(0) == Approx(1.516).epsilon(0.001));
  REQUIRE(pos(1) == Approx(1.297).epsilon(0.001));
  REQUIRE(pos(2) == Approx(3.439).epsilon(0.001));

  Eigen::ArrayXd bstPos = p.getBestPosition();
  REQUIRE(pos.size() == 3);
  REQUIRE(bstPos(0) == Approx(1.516).epsilon(0.001));
  REQUIRE(bstPos(1) == Approx(1.297).epsilon(0.001));
  REQUIRE(bstPos(2) == Approx(3.439).epsilon(0.001));

  Eigen::ArrayXd vel = p.getVelocity();
  REQUIRE(pos.size() == 3);
  REQUIRE(vel(0) == Approx(6.631).epsilon(0.001));
  REQUIRE(vel(1) == Approx(4.819).epsilon(0.001));
  REQUIRE(vel(2) == Approx(-6.300).epsilon(0.001));

  auto params = p.getParameters();
  REQUIRE(params.size() == 3);
  REQUIRE(params["x1"] == Approx(1.516).epsilon(0.001));
  REQUIRE(params["x2"] == Approx(1.297).epsilon(0.001));
  REQUIRE(params["x3"] == Approx(3.439).epsilon(0.001));

  auto bstParams = p.getBestParameters();
  REQUIRE(bstParams.size() == 3);
  REQUIRE(bstParams["x1"] == Approx(1.516).epsilon(0.001));
  REQUIRE(bstParams["x2"] == Approx(1.297).epsilon(0.001));
  REQUIRE(bstParams["x3"] == Approx(3.439).epsilon(0.001));
}

TEST_CASE("Particle Parameters are ordered", "[Particle]") {
  RandomGenerator::seed(50);

  ParameterSpace parameters;
  parameters["x1"] = std::make_pair(-1, 1);
  parameters["x2"] = std::make_pair(10, 50);
  parameters["x3"] = std::make_pair(1, 2);
  parameters["x4"] = std::make_pair(0.01, 0.02);

  Particle p(parameters);

  auto params = p.getParameters();
  REQUIRE(params.size() == 4);
  REQUIRE(params["x1"] == Approx(-0.741).epsilon(0.001));
  REQUIRE(params["x2"] == Approx(12.975).epsilon(0.001));
  REQUIRE(params["x3"] == Approx(1.609).epsilon(0.001));
  REQUIRE(params["x4"] == Approx(0.010).epsilon(0.001));
}
