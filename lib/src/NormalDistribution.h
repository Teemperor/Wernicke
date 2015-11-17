
#ifndef WERNICKE_NORMALDISTRIBUTION_H
#define WERNICKE_NORMALDISTRIBUTION_H


class NormalDistribution {
    const double euler = 2.718281828459045;

    double mean_, variance_;

public:
    NormalDistribution(double mean = 0, double variance = 1) : mean_(mean), variance_(variance) {
    }

    double probability(double value);
};


#endif //WERNICKE_NORMALDISTRIBUTION_H
