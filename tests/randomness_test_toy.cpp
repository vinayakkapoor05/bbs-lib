#include <iostream>
#include <chrono>
#include <cmath>
#include "bbs_toy.hpp"

using namespace bbs_toy;
using namespace std::chrono;

int main (){

    unsigned long p = generateBlumPrime(3000000, 6000000);
    unsigned long q = generateBlumPrime(6000000, 9000000);

    unsigned long n = p * q;

    unsigned long seed = 12345;
    BlumBlumShub bbs(p, q, seed);

    const size_t numBits = 1000000;
    size_t countOnes = 0;
     

    auto start = high_resolution_clock::now();

    for (size_t i = 0; i < numBits; i++){
        if (bbs.nextBit() == 1){
            countOnes += 1;
        
    }}

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start).count();

    double proportion = static_cast<double>(countOnes) / numBits;

    std::cout << "Randomness Test (Toy BBS)" << std::endl;
    std::cout << "  Total bits generated: " << numBits << std::endl;
    std::cout << "  Count of 1s: " << countOnes << std::endl;
    std::cout << "  Proportion of 1s: " << proportion << std::endl;
    std::cout << "  Expected proportion: 0.5" << std::endl;
    std::cout << "  Duration: " << duration << " microseconds" << std::endl;

    // Perform a chi-squared test
    double expected = numBits / 2;

    double chiSquared = (std::pow(countOnes - expected, 2) + std::pow((numBits - countOnes) - expected, 2))/2;
    std::cout << "  Chi-squared Statistic: " << chiSquared << std::endl;

    std::cout << "  Expected value is 0" << std::endl;



    return 0;








}