#include <iostream>
#include <chrono>
#include "bbs_toy.hpp"

int main() {
    using namespace bbs_toy;
    using namespace std::chrono;

    std::cout << "Experiment: Factorization Time vs Partial Knownledge of p and/or q" << std::endl;

    unsigned int totalBits = 16;
    unsigned long lower = 1UL << (totalBits - 1);
    unsigned long upper = (1UL << totalBits);

    unsigned long p_actual = generateBlumPrime(lower, upper);
    unsigned long q_actual = generateBlumPrime(lower, upper);
    unsigned long n = p_actual * q_actual;

    std::cout << "Actual Blum primes" << std::endl; 
    std::cout << "p = " << p_actual << std::endl;
    std::cout << "q = " << q_actual << std::endl;
    std::cout << "n = p * q = " << n << std::endl;

    for (unsigned int knownBits = 4; knownBits <= totalBits; knownBits += 4){
        unsigned long mask = ((1UL << knownBits) - 1) << (totalBits - knownBits);

        unsigned long p_known = p_actual & mask;
        unsigned long q_known = q_actual & mask;

        unsigned long p_unknown_range = 1UL << (totalBits - knownBits);
        unsigned long q_unknown_range = 1UL << (totalBits - knownBits);

        auto start = high_resolution_clock::now();
        bool p_found = false;
        bool q_found = false;

        unsigned long p_recovered = 0;
        unsigned long q_recovered = 0;

        // Brute force lower bits for p
        for (unsigned long candidate = 0; candidate < p_unknown_range; candidate++){
            unsigned long test_p = p_known | candidate;
            if (test_p == p_actual){
                p_found = true;
                p_recovered = test_p;
                break;
            }
        }

        // Brute force lower bits for q

        for (unsigned long candidate = 0; candidate < q_unknown_range; candidate++){
            unsigned long test_q = q_known | candidate;
            if (test_q == q_actual){
                q_found = true;
                q_recovered = test_q;
                break;
            }
        }   

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start).count();
        std::cout << "Known bits: " << knownBits << " -> Unknown Range: " << p_unknown_range << ", " << q_unknown_range << ", Time: " << duration << " microseconds" << std::endl;

        if (p_found && q_found){
            std::cout << "p recovered: " << p_recovered << ", q recovered: " << q_recovered << std::endl;
        }

        std::cout << std::endl;
    
    }
    return 0;
}
      
