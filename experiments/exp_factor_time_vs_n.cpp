#include <iostream>
#include <chrono>
#include "bbs_toy.hpp"
#include "bbs_utils.hpp"

int main(){
    using namespace bbs_toy;
    using namespace std::chrono;
    using namespace bbs_utils;

    std::cout << "Experiment: Factorization Time vs Blum Prime Bit Length" << std::endl;

    for (unsigned int bitLength = 8; bitLength <= 32; bitLength += 4){
        unsigned long lower = 1UL << (bitLength - 1);
        unsigned long upper = (1UL << bitLength);

        unsigned long p = generateBlumPrime(lower, upper);
        unsigned long q = generateBlumPrime(lower, upper);
        unsigned long n = p * q;

        auto start = high_resolution_clock::now();
        auto factors = naiveFactor(n);

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start).count();

        std::cout << "Bit length: " << bitLength 
        << " -> n bit length: " << bitLength * 2
        << ", Factorization time: " << duration << " microseconds" << std::endl;

    }   

    return 0;

}