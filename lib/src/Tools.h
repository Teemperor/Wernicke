
#ifndef WERNICKE_TOOLS_H
#define WERNICKE_TOOLS_H

#include <vector>
#include "Range.h"

class Tools {

public:
    static double normalize(std::vector<double>& v, Range range = Range()) {
        double max = 0;
        for (std::size_t i = 0; i < v.size(); i++) {
            if (!range.contains(i))
                continue;

            double value = v[i];

            if (value > max) {
                max = value;
            }
            if (-value > max) {
                max = -value;
            }
        }
        for (std::size_t i = 0; i < v.size(); i++) {
            v[i] = v[i] / max;
        }
        return max;
    }

    static double average(std::vector<double>& v, Range range = Range()) {
        double result = 0;
        double count = 0;

        for (std::size_t i = 0; i < v.size(); i++) {
            if (!range.contains(i))
                continue;
            count++;
            result += v[i];
        }

        return result / count;
    }

    static double variance(std::vector<double>& v, Range range = Range()) {
        double avg = average(v, range);
        return variance(v, avg, range);
    }

    static double variance(std::vector<double>& v, double average, Range range = Range()) {
        double result = 0;
        double dataPoints = 0;

        for (std::size_t i = 0; i < v.size(); i++) {
            if (!range.contains(i))
                continue;

            double diff = v[i] - average;
            result += diff * diff;
            dataPoints++;
        }

        return result / dataPoints;
    }
};


#endif //WERNICKE_TOOLS_H
