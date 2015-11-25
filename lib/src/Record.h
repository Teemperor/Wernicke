
#ifndef WERNICKE_RECORD_H
#define WERNICKE_RECORD_H


#include <vector>
#include <string>
#include <cstdint>

#include "Tools.h"

class Record {

    double maxAltitude_ = 1;
    std::vector<double> altitudes_;

public:
    Record() {
    }
    Record(double* data, std::size_t size) {
        std::vector<double> altitudes;
        altitudes.resize(size);
        for (std::size_t i = 0; i < size; i++) {
            altitudes[i] = data[i];
        }
        setAltitudes(altitudes);
    }

    static Record* fromRawFile(const std::string& file);

    void setAltitudes(const std::vector<double>& altitudes) {
        altitudes_ = altitudes;
        maxAltitude_ = Tools::normalize(altitudes_);
    }

    const std::vector<double>& altitudes() const {
        return altitudes_;
    }
};


#endif //WERNICKE_RECORD_H
