#include <iostream>
#include <chrono>
#include <iostream>
#include "bbs_toy.hpp"

int main() {


    using namespace bbs_toy;
    using namespace std::chrono;

    const unsigned int totalBits = 16;
    unsigned long actual_seed = 0xABCD;

    unsigned long p = generateBlumPrime(300,600);
    unsigned long q = generateBlumPrime(600,900);

    unsigned long n = p * q;

    std::cout << "Experiment: Factorization Time vs Partial Seed Exposure" << std::endl;
    std::cout << "Actual Seed: " << actual_seed << std::hex << std::dec << std::endl;
    for (unsigned int knownBits = 4; knownBits <= totalBits; knownBits +=4) {
        // Construct a mask for the upper known bits
        unsigned long mask = ((1UL << knownBits) - 1) << (totalBits - knownBits);
        unsigned long known_part = actual_seed & mask;
        unsigned long unknown_range = 1UL << (totalBits - knownBits);

        auto start = high_resolution_clock::now();
        bool found = false;

        unsigned long recovered_seed = 0;

        for (unsigned long candidate = 0; candidate < unknown_range; candidate ++){
            unsigned long test_seed = known_part | candidate;
            BlumBlumShub testBBS(p, q, test_seed);
            auto test_keystream = testBBS.nextBytes(10);

            BlumBlumShub victimBBS(p, q, actual_seed);
            auto victim_keystream = victimBBS.nextBytes(10);

            if (test_keystream == victim_keystream){
                found = true;
                recovered_seed = test_seed;
                break;
            }





        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start).count();
        std::cout << "Known bits: " << knownBits << " -> Unknown Range: " <<  unknown_range << ", Time: " << duration << " microseconds" << std::endl;

        if (found){
            std::cout << "Recovered seed: 0x" << recovered_seed << std::hex << std::dec << std::endl;

        }


    }


    return 0;









}