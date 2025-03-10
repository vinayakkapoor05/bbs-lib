#include <iostream>
#include <vector>
#include <cstdio>
#include <chrono>
#include "bbs_toy.hpp" // Reuse generateBlumPrime function
#include "bbs_sidechannel.hpp"


int main(){
    using namespace bbs_toy;
    using namespace bbs_sidechannel;

    // Victim's side
    unsigned long p = generateBlumPrime(300, 600);
    unsigned long q = generateBlumPrime(600, 900);
    unsigned long n = p * q;


    unsigned long seed = 12345;

    std::cout << "Side-channel BBS Simulation Demo\n" << std::endl;
    std::cout << "Victim's Parameters:" << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;
    std::cout << "n = p * q = " << n << std::endl;
    std::cout << "Seed = " << seed << std::endl;


    ToySideChannelBBS victimBBS(p, q, seed);

    // Measure and report the time taken for each nextBit call

    const int numBits = 20;
    std::cout << "Measuring time taken for " << numBits << " nextBit calls" << std::endl;
    for (int i = 0; i < numBits; i++){
        auto start = std::chrono::high_resolution_clock::now();
        unsigned int bit = victimBBS.nextBit();
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Bit " << i << ": " << bit << " Time: " << duration << " microseconds" << std::endl;


    }

    // Additionally generate some random bytes and display them

    std::vector<unsigned char> bytes = victimBBS.nextBytes(16);
    std::cout << "16 random bytes: ";
    for (auto b : bytes){
        std::printf("%02x", b);
    }
    std::cout << "\n";

    return 0;

}