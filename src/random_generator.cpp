#include "random_generator.hpp"
#include <random>

using namespace Optima;

std::mt19937 RandomGenerator::m_generator = std::mt19937(std::random_device()());
