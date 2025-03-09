#include <iostream>
#include "bbs_toy.hpp"
#include "bbs_utils.hpp"

int main()
{
    using namespace bbs_toy;
    using namespace bbs_utils;

    // Victim's side

    unsigned long p = generateBlumPrime(300, 600);
    unsigned long q = generateBlumPrime(600, 900);
    unsigned long n = p * q;

    std::cout << "Victim's Blum primes" << std::endl;
    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;
    std::cout << "n = p * q = " << n << std::endl;

    unsigned long seed = 12345;
    BlumBlumShub victimBBS(p, q, seed);

    // Attacker's side

    std::pair<unsigned long, unsigned long> factors = naiveFactor(n);
    if (factors.first == 0 && factors.second == 0)
    {
        std::cout << "Attacker: Failed to factor n" << std::endl;
        return 1;
    }

    std::cout << "Attacker's Factorization" << std::endl;
    std::cout << " Factor 1: " << factors.first << std::endl;
    std::cout << " Factor 2: " << factors.second << std::endl;

    if ((factors.first == p && factors.second == q) || (factors.first == q && factors.second == p))
    {
        std::cout << "Attacker: Successful factorization! Recovered factors match victim's primes." << std::endl;
    } else {
        std::cout << "Attacker: Factorization succeeded, but the factors do not match exactly." << std::endl;
    }
        return 0;
    }