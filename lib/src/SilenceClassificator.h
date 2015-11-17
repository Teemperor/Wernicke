
#ifndef WERNICKE_SILENCECLASSIFICATOR_H
#define WERNICKE_SILENCECLASSIFICATOR_H


#include "NormalDistribution.h"
#include "Record.h"

class SilenceClassificator {

    NormalDistribution silence_;
    NormalDistribution speech_;

public:
    SilenceClassificator(Record& silenceSample, Record& speechSample)
            : silence_(silenceSample.averageEnergy(), silenceSample.energyVariance()),
              speech_(speechSample.averageEnergy(), speechSample.energyVariance())
    {
    }

    SilenceClassificator()
            : silence_(0, 0.3),
              speech_(0.5, 1)
    {
    }

    void stripSilence(Record* stripSilence) {

    }

};


#endif //WERNICKE_SILENCECLASSIFICATOR_H
