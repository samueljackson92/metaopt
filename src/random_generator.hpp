#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H

#include <random>

namespace MetaOpt {

class RandomGenerator {

public:
  static void seed(const int seed) {
    m_generator.seed(seed);
  }

  template<typename T>
  static T uniform(const T lower = -1.0, const T upper = 1.0) {
    std::uniform_real_distribution<T> distribution(lower, upper);
    return distribution(m_generator);
  }

private:
  static std::mt19937 m_generator;
};
}

#endif
