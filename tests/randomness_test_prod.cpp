#include <iostream>
#include <chrono>
#include <cmath>
#include "bbs_production.hpp"

using namespace bbs_production;
using namespace std::chrono;

int main() {
    unsigned int bitLength = 512;
    std::cout << "Randomness Test (Production BBS)" << std::endl;
    std::cout << "Generating Blum primes of " << bitLength << " bits each..." << std::endl;
    
    mpz_class p = generateBlumPrime(bitLength);
    mpz_class q = generateBlumPrime(bitLength);
    mpz_class n = p * q;
    
    std::cout << "p bit length: " << mpz_sizeinbase(p.get_mpz_t(), 2) << std::endl;
    std::cout << "q bit length: " << mpz_sizeinbase(q.get_mpz_t(), 2) << std::endl;
    std::cout << "n bit length: " << mpz_sizeinbase(n.get_mpz_t(), 2) << std::endl;
    
    mpz_class seedCandidate("123456789");
    
    BlumBlumShub bbs(p, q, seedCandidate);
    
    const size_t numBits = 1000000;
    size_t countOnes = 0;
    
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < numBits; i++) {
        if (bbs.nextBit() == 1) {
            countOnes++;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start).count();
    
    double proportion = static_cast<double>(countOnes) / numBits;
    
    std::cout << "\nRandomness Test Results:" << std::endl;
    std::cout << "  Total bits generated: " << numBits << std::endl;
    std::cout << "  Count of 1's: " << countOnes << std::endl;
    std::cout << "  Proportion of 1's: " << proportion << std::endl;
    std::cout << "  Expected proportion: 0.5" << std::endl;
    std::cout << "  Duration: " << duration << " microseconds" << std::endl;
    
    // Compute chi-square statistic 
    double expected = numBits / 2.0;
    double chiSquared = (std::pow(countOnes - expected, 2) + std::pow((numBits - countOnes) - expected, 2)) / expected;
    std::cout << "  Chi-Squared Statistic: " << chiSquared << std::endl;
    std::cout << "  Expected value is 0"  << std::endl;

    
    return 0;
}
