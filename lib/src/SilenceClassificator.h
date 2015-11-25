
#ifndef WERNICKE_SILENCECLASSIFICATOR_H
#define WERNICKE_SILENCECLASSIFICATOR_H


#include "NormalDistribution.h"
#include "Record.h"
#include "RecordPart.h"

class SilenceClassificator {

    NormalDistribution silence_;
    NormalDistribution speech_;

public:
    SilenceClassificator(RecordPart& silenceSample, RecordPart& speechSample)
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
