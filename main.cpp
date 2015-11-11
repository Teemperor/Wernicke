#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

/*
   This computes an in-place complex-to-complex FFT
   x and y are the real and imaginary arrays of 2^m points.
   dir =  1 gives forward transform
   dir = -1 gives reverse transform
*/
short FFT(short int dir, long m, std::vector<double>& x, std::vector<double>& y)
{
    long n,i,i1,j,k,i2,l,l1,l2;
    double c1,c2,tx,ty,t1,t2,u1,u2,z;

    /* Calculate the number of points */
    n = 1;
    for (i=0;i<m;i++)
        n *= 2;

    /* Do the bit reversal */
    i2 = n >> 1;
    j = 0;
    for (i=0;i<n-1;i++) {
        if (i < j) {
            tx = x[i];
            ty = y[i];
            x[i] = x[j];
            y[i] = y[j];
            x[j] = tx;
            y[j] = ty;
        }
        k = i2;
        while (k <= j) {
            j -= k;
            k >>= 1;
        }
        j += k;
    }

    /* Compute the FFT */
    c1 = -1.0;
    c2 = 0.0;
    l2 = 1;
    for (l=0;l<m;l++) {
        l1 = l2;
        l2 <<= 1;
        u1 = 1.0;
        u2 = 0.0;
        for (j=0;j<l1;j++) {
            for (i=j;i<n;i+=l2) {
                i1 = i + l1;
                t1 = u1 * x[i1] - u2 * y[i1];
                t2 = u1 * y[i1] + u2 * x[i1];
                x[i1] = x[i] - t1;
                y[i1] = y[i] - t2;
                x[i] += t1;
                y[i] += t2;
            }
            z =  u1 * c1 - u2 * c2;
            u2 = u1 * c2 + u2 * c1;
            u1 = z;
        }
        c2 = sqrt((1.0 - c1) / 2.0);
        if (dir == 1)
            c2 = -c2;
        c1 = sqrt((1.0 + c1) / 2.0);
    }

    /* Scaling for forward transform */
    if (dir == 1) {
        for (i=0;i<n;i++) {
            x[i] /= n;
            y[i] /= n;
        }
    }

    return 1;
}

std::vector<int32_t> readPCM() {
    std::ifstream file("/home/teemperor/Dokumente/ASE/audio/adrei02.raw");

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


double calculateAverageEnergy(const std::vector<double>& energy, std::size_t start, std::size_t end, bool invert) {
    double result = 0;
    uint64_t dataPoints = 0;

    for (std::size_t i = 0; i < energy.size(); i++) {
        if (i >= start && i < end) {
            if (!invert) {
                result += energy[i];
                dataPoints++;
            }
        } else {
            if (invert) {
                result += energy[i];
                dataPoints++;
            }
        }
    }

    return result / dataPoints;
}

double calculateVariance(const std::vector<double>& energy, std::size_t start, std::size_t end, bool invert) {
    double average = calculateAverageEnergy(energy, start, end, invert);
    double result = 0;
    uint64_t dataPoints = 0;

    for (std::size_t i = 0; i < energy.size(); i++) {
        if (i >= start && i < end) {
            if (!invert) {
                double diff = energy[i] - average;
                result += diff * diff;
                dataPoints++;
            }
        } else {
            if (invert) {
                double diff = energy[i] - average;
                result += diff * diff;
                dataPoints++;
            }
        }
    }

    return result / dataPoints;
}

std::vector<double> calculateEnergy(const std::vector<int>& amplitudes, std::size_t windowsize, std::size_t offset) {
    std::vector<uint64_t> result;
    double max = 0;

    for(std::size_t i = 0; i < amplitudes.size() - offset; i += offset) {
        uint64_t energy = 0;
        for (std::size_t j = i; j < i + windowsize; j++) {
            energy += (myabs(amplitudes[j]) * myabs(amplitudes[j]));
        }
        result.push_back(energy);
        if (energy > max) {
            max = energy;
        }
    }

    std::vector<double> doubleResult;

    for (uint64_t value : result) {
        doubleResult.push_back(value / max);
    }

    return doubleResult;
}

const double euler = 2.718281828459045;

double normalDistributionProbability(double mean, double variance, double value) {
    static double constFactor = 1.0 / sqrt(2 * M_PI);

    double x = (value - mean) / variance;

    return constFactor * pow(euler, -0.5 * x * x);
}

int main(void)
{
	auto result = readPCM();

    auto energy = calculateEnergy(result, 160, 10);
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
    }

    double speakingAvgEnergy = 0.342522; // calculateAverageEnergy(energy, 100, 500, false);
    double silenceAvgEnergy = 0.00188455; // calculateAverageEnergy(energy, 100, 500, true);
    double speakingAvgEnergyVariance = 0.121843; // calculateVariance(energy, 100, 500, false);
    double silenceAvgEnergyVariance = 0.01; // calculateVariance(energy, 100, 500, true);

    std::cout << "Speaking avg. energy: " << speakingAvgEnergy << "\n";
    std::cout << "Silence avg. energy: " << silenceAvgEnergy << "\n";

    std::cout << "Speaking avg. energy variance: " << speakingAvgEnergyVariance << "\n";
    std::cout << "Silence avg. energy variance: " << silenceAvgEnergyVariance << "\n";


    std::vector<double> speakingProb;
    std::vector<double> silenceProb;
    std::vector<int> isSpeaking;


    for (auto energyInWindow : energy) {
        double probabilitySpeaking = normalDistributionProbability(speakingAvgEnergy, speakingAvgEnergyVariance, energyInWindow);
        double probabilitySilence = normalDistributionProbability(silenceAvgEnergy, silenceAvgEnergyVariance, energyInWindow);

        speakingProb.push_back(probabilitySpeaking);
        silenceProb.push_back(probabilitySilence);

        if (probabilitySpeaking > probabilitySilence) {
            isSpeaking.push_back(1);
        } else {
            isSpeaking.push_back(0);
        }
    }

    unsigned fftWindowSizePower = 8;
    unsigned fftWindowSize = 1u << fftWindowSizePower;
    std::vector<double> realPart, imaginaryPart;
    realPart.resize(fftWindowSize, 0);
    imaginaryPart.resize(fftWindowSize, 0);

    for (uint64_t i = 0; i < (int) result.size() - fftWindowSize; i += fftWindowSize) {

        for (uint64_t j = i; j < i + fftWindowSize; j++) {
            realPart[j - i] = result[j];
        }

        for (std::uint64_t j = 0; j < fftWindowSize; j++) {
            imaginaryPart[j] = 0;
        }

        FFT(1, fftWindowSizePower, realPart, imaginaryPart);
    }

    {
        std::ofstream myfile;
        myfile.open ("/home/teemperor/Dokumente/ASE/ubung3/isSpeaking.dat");

        for(auto i : isSpeaking) {
            myfile << i << "\n";
        }
        myfile.close();
    }

    {
        std::ofstream myfile;
        myfile.open ("/home/teemperor/Dokumente/ASE/ubung3/silenceProb.dat");

        for(auto i : silenceProb) {
            myfile << i << "\n";
        }
        myfile.close();
    }

    {
        std::ofstream myfile;
        myfile.open ("/home/teemperor/Dokumente/ASE/ubung3/speakingProb.dat");

        for(auto i : speakingProb) {
            myfile << i << "\n";
        }
        myfile.close();
    }


    system("gnuplot /home/teemperor/Dokumente/ASE/ubung3/gnuplot.gp");

    return 0;
}