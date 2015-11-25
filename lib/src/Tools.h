
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
        uint64_t count = 0;

        for (std::size_t i = 0; i < v.size(); i++) {
            if (!range.contains(i))
                continue;
            count++;
            result += v[i];
        }

        return (double) (result / count);
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

        return (double) (result / dataPoints);
    }


    std::uint32_t static toNextPowerOf2(uint32_t v) {
        v--;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        v |= v >> 8;
        v |= v >> 16;
        v++;
        return v;
    }

    unsigned static log2(uint32_t i) {
        unsigned result = 0;
        while (i >>= 1) { ++result; }
        return result;
    }
};


#endif //WERNICKE_TOOLS_H
