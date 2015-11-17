
#include "NormalDistribution.h"
#include <cmath>

double NormalDistribution::probability(double value) {
    static double constFactor = 1.0 / sqrt(2 * M_PI);

    double x = (value - mean_) / variance_;

    return constFactor * pow(euler, -0.5 * x * x);
}