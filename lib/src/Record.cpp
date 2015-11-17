
#include "Record.h"
#include <fstream>
#include <iostream>

Record *Record::fromRawFile(const std::string& path) {
    std::ifstream file(path);

    std::vector<double> result;
    result.reserve(100000);

    if(file.is_open())
    {
        while (true) {
            char buf[2];

            file.read(buf, 2);

            char tmp = buf[1];
            buf[1] = buf[0];
            buf[0] = tmp;

            if (file.fail()) {
                break;
            }

            int16_t value = ((int16_t*) buf)[0];

            result.push_back(value);
        }
    } else {
        std::cerr << "Error opening file" << std::endl;
        abort();
    }

    Record* record = new Record();
    record->setAltitudes(result);
    return record;
}