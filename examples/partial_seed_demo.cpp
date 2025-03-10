#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdint>
#include "bbs_toy.hpp"

// Simulate a scenario  where the secret seed is 16 bits but the attacker only knows the upper 8 bits
// Attacker tries all 256 possibilities for the lower 8 bits

int main(){
    using namespace bbs_toy;
    unsigned long p = generateBlumPrime(300, 600);
    unsigned long q = generateBlumPrime(600, 900);

    unsigned long n = p * q;

    unsigned long actual_seed = 0xABCD; // 16 bits

    std::cout << "Victim's Parameters:" << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;
    std::cout << "n = p * q = " << n << std::endl;
    std::cout << "Actual Seed = 0x" << actual_seed << std::endl;

    BlumBlumShub victimBBS(p, q, actual_seed);

    // Generate a short keystream to verify the seed
    const size_t keystream_length = 10;

    std::vector<unsigned char> victim_keystream = victimBBS.nextBytes(keystream_length);

    std::cout << "Victim's Keystream (hex): ";
    for (auto b : victim_keystream){
        std::printf("%02x", b);
    }

    std::cout << "\n";

    // Attacker's side

    unsigned long known_part = actual_seed  & 0xFF00; // Upper 8 bits
    std::cout << "Attacker's knows upper 8 bits: 0x" << std::hex << (known_part >> 8) << std::dec << std::endl;

    unsigned long recovered_seed = 0;
    bool found = false;

    for (unsigned long candidate = 0; candidate < 256; candidate++){
        unsigned long test_seed = known_part | candidate;
        BlumBlumShub attackerBBS(p, q, test_seed);
        std::vector<unsigned char> attacker_keystream = attackerBBS.nextBytes(keystream_length);
        if (attacker_keystream == victim_keystream){
            recovered_seed = test_seed;
            found = true;
            break;
        }

    } 

    if (found){
        std::cout << "Attacker: Recovered the full seed: 0x" << std::hex << recovered_seed << std::dec << std::endl;
    } else {
        std::cout << "Attacker: Failed to recover seed." << std::endl;
    }

    return 0;

}