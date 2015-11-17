#include <assert.h>
#include "../src/Record.h"
#include "../src/SilenceClassificator.h"
#include <iostream>

int main() {
    Record* dreiSound = Record::fromRawFile("adrei01.raw");
    Record* silence = Record::fromRawFile("silence.raw");

    SilenceClassificator classificator;


    std::cout << dreiSound->averageEnergy() << std::endl;
    std::cout << silence->averageEnergy() << std::endl;

}