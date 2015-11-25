#include <assert.h>
#include "../src/Record.h"
#include "../src/SilenceClassificator.h"
#include <iostream>

int main() {
    assert(Tools::toNextPowerOf2(3) == 4);
    assert(Tools::toNextPowerOf2(4) == 4);

    assert(Tools::log2(4) == 2);
    assert(Tools::log2(8) == 3);
}