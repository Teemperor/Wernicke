#include <assert.h>
#include "../src/Record.h"
#include "../src/SilenceClassificator.h"
#include <iostream>

int main() {
    Record* dreiSound = Record::fromRawFile("adrei01.raw");
    Record* silence = Record::fromRawFile("silence.raw");

    SilenceClassificator classificator;

    RecordPart dreiSoundPart(dreiSound, 0, dreiSound->altitudes().size());
    RecordPart silencePart(dreiSound, 0, silence->altitudes().size());

    std::cout << dreiSoundPart.averageEnergy() << std::endl;
    std::cout << silencePart.averageEnergy() << std::endl;

}