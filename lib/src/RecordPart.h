#ifndef WERNICKE_RECORDPART_H
#define WERNICKE_RECORDPART_H


#include <cmath>
#include <iostream>
#include "Record.h"

class RecordPart {

    /*
     * from http://paulbourke.net/miscellaneous/dft/
     * This computes an in-place complex-to-complex FFT
     * x and y are the real and imaginary arrays of 2^m points.
     * dir =  1 gives forward transform
     * dir = -1 gives reverse transform
     */
    void FFT(short int dir, long m, double *x, double *y);

    Record* record_;

    std::size_t start_, end_;

    double averageEnergy_ = 0;
    std::vector<double> frequencies_;
    double energyVariance_;

    void init(std::size_t size);

public:

    RecordPart(Record* record, std::size_t start, std::size_t size) : record_(record), start_(start), end_(start + size) {
        init(size);
    }

    RecordPart(Record* record) : record_(record), start_(0), end_(record->altitudes().size()) {
        init(end_ - start_);
    }

    double averageEnergy() const {
        return averageEnergy_;
    }

    double energyVariance() const {
        return energyVariance_;
    }

    const std::vector<double>& frequencies() const {
        return frequencies_;
    }

};


#endif //WERNICKE_RECORDPART_H
