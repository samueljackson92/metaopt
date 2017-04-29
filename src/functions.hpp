#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "types.hpp"
#include <Eigen/Core>
#include <cmath>
#include <numeric>

namespace Optima {

class TestFunctions {

public:

    /**
     * N-Dimensional generalization of the Ackley function
     *
     * This function has a minimum when all parameter values are zero.
     * The hyper parameters for this function are hard coded to the following:
     * a = 20
     * b = 0.2
     * c = 2 * pi
     *
     * @param params :: n dimensional array of x values
     * @return value of the function evaluated with the given parameters
     */
    static double ackley(const Parameters &params) {
        const double a = 20;
        const double b = 0.2;
        const double c = 2 * M_PI;

        double powerSum = std::accumulate(params.begin(), params.end(), 0, 
                [](const double sum, const std::pair<std::string, double>& item) {
                    return sum + std::pow(item.second, 2.0);
                });

        double cosSum = std::accumulate(params.begin(), params.end(), 0, 
                [&c](const double sum, const std::pair<std::string, double>& item) {
                    return sum + std::cos(c*item.second);
                });

        cosSum *= 1. / params.size();
        powerSum *= 1. / params.size();
        powerSum = std::sqrt(powerSum);

        return -a * std::exp( -b * powerSum ) - std::exp(cosSum) + a + std::exp(1);
    }

    /**
     * N-Dimensional generalization of the Rosenbrock function
     *
     * The minimum of this function will be at zero
     *
     * @param vec :: n dimensional array of x values
     * @return value of the function evaluated at the point defined by vec
     */
    static double rosen(const Parameters &params) {
        using namespace std;
        double y = 0;
        for (size_t i = 0; i < params.size() - 1; ++i) {
            const double x1 = params.at("x" + std::to_string(i));
            const double x2 = params.at("x" + std::to_string(i + 1));
            y += 100 * pow(x2 - pow(x1, 2.0), 2.0) + pow(1 - x1, 2.0);
        }

        return y;
    }

    /**
     * N-Dimensional parabolic function centered on the origin.
     *
     * The function has the form x1**2 + x2**2 + ... + xn**2 = y
     *
     * The minimum of this function will be at zero
     *
     * @param vec :: n dimensional arry of x values
     * @return value of the function evaludated at the point defined by vec
     */
    static double parabola(const Parameters &params) {
        using namespace std;
        double y = 0;
        for (const auto &param : params)
            y += std::pow(param.second, 2.0);

        return y;
    }

};
}
#endif // FUNCTIONS_H
