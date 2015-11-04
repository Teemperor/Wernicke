#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>


std::vector<int32_t> readPCM() {
    std::ifstream file("/home/teemperor/Dokumente/ASE/audio/adrei01.raw");

    std::vector<int32_t> result;
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
    return result;
}

uint64_t myabs(int value) {
    if (value < 0)
        value = -value;
    return static_cast<uint32_t>(value);
}

std::vector<uint64_t> calculateEnergy(const std::vector<int>& amplitudes, std::size_t windowsize, std::size_t offset) {
    std::vector<uint64_t> result;


    for(std::size_t i = 0; i < amplitudes.size() - offset; i += offset) {
        uint64_t energy = 0;
        for (std::size_t j = i; j < i + windowsize; j++) {
            energy += (myabs(amplitudes[j]) * myabs(amplitudes[j]));
        }
        result.push_back(energy);
    }


    return result;
}

int main(void)
{
	auto result = readPCM();

    auto energy = calculateEnergy(result, 160, 160);
    {
        std::ofstream myfile;
        myfile.open ("/home/teemperor/Dokumente/ASE/ubung3/amplituden.dat");

        for(auto i : result) {
            myfile << i << "\n";
        }
        myfile.close();
    }
    {
        std::ofstream myfile;
        myfile.open ("/home/teemperor/Dokumente/ASE/ubung3/energy.dat");

        for(auto i : energy) {
            myfile << i << "\n";
        }
        myfile.close();

        system("gnuplot /home/teemperor/Dokumente/ASE/ubung3/gnuplot.gp");
    }


    return 0;
}