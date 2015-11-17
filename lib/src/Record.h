
#ifndef WERNICKE_RECORD_H
#define WERNICKE_RECORD_H


#include <vector>
#include <string>
#include <cstdint>

#include "Tools.h"

class Record {

    double maxAltitude_ = 1;
    std::vector<double> altitudes_;
    std::vector<double> energy_;
    double averageEnergy_, energyVariance_;

public:
    Record() {
    }
    Record(float* data, std::size_t size) {
        std::vector<double> altitudes;
        altitudes.resize(size);
        for (std::size_t i = 0; i < size; i++) {
            altitudes[i] = data[i];
        }
        setAltitudes(altitudes);
    }

    static Record* fromRawFile(const std::string& file);

    void setAltitudes(const std::vector<double> altitudes) {
        altitudes_ = altitudes;
        maxAltitude_ = Tools::normalize(altitudes_);
        energy_.resize(altitudes_.size());
        for (std::size_t i = 0; i < altitudes_.size(); i++) {
            energy_[i] = altitudes_[i] * altitudes_[i];
        }
        averageEnergy_ = Tools::average(energy_);
        energyVariance_ = Tools::variance(energy_);
    }

    double averageEnergy() const {
        return averageEnergy_;
    }

    double energyVariance() const {
        return energyVariance_;
    }

    const std::vector<double>& altitudes() const {
        return altitudes_;
    }

    const std::vector<double>& energy() const {
        return energy_;
    }
};


#endif //WERNICKE_RECORD_H
