
#include <catch.hpp>
#include "../random_generator.hpp"

using namespace MetaOpt;

TEST_CASE( "Random Generator Uniform Double", "[RandomGenerator.uniform]" ) {
  RandomGenerator::seed(50);
  auto value = RandomGenerator::uniform<double>();
  REQUIRE(value == Approx(-0.7416508344).epsilon(0.001));
}

TEST_CASE( "Random Generator Uniform Double Range", "[RandomGenerator.uniform]" ) {
  RandomGenerator::seed(50);
  auto value = RandomGenerator::uniform<double>(1, 3.0);
  REQUIRE(value == Approx(1.2583491656).epsilon(0.001));
}

TEST_CASE( "Random Generator Uniform Float", "[RandomGenerator.uniform]" ) {
  RandomGenerator::seed(50);
  auto value = RandomGenerator::uniform<float>();
  REQUIRE(value == Approx(-0.0108f).epsilon(0.001));
}

TEST_CASE( "Random Generator Uniform Float Range", "[RandomGenerator.uniform]" ) {
  RandomGenerator::seed(50);
  auto value = RandomGenerator::uniform<float>(1, 3.0);
  REQUIRE(value == Approx(1.9892f).epsilon(0.001));
}

TEST_CASE( "Random Generator Reseed", "[RandomGenerator.seed]" ) {
  RandomGenerator::seed(50);
  auto value = RandomGenerator::uniform<float>(1, 3.0);
  REQUIRE(value == Approx(1.9892f).epsilon(0.001));
  value = RandomGenerator::uniform<float>(1, 3.0);
  REQUIRE(value == Approx(1.25835f).epsilon(0.001));

  RandomGenerator::seed(50);
  value = RandomGenerator::uniform<float>(1, 3.0);
  REQUIRE(value == Approx(1.9892f).epsilon(0.001));
}
