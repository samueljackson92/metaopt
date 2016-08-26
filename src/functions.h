#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <cmath>
#include <Eigen/Core>

/**
 * N-Dimensional generalization of the Rosenbrock function
 * @param vec :: n dimensional array of x values
 * @return value of the function evaluated at the point defined by vec
 */
double rosen (const Eigen::ArrayXd& vec)
{
    using namespace std;
    double y = 0;
    for (size_t i = 0; i < vec.size()-1; ++i) {
        const double x1 = vec[i];
        const double x2 = vec[i+1];
        y += 100 * pow(x2 - pow(x1, 2.0), 2.0) + pow(1 - x1, 2.0);
    }

    return y;
}

#endif // FUNCTIONS_H
