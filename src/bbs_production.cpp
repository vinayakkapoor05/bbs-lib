#include "bbs_production.hpp"
#include <stdexcept>
#include <random>


// Use GMP's mpz_probab_prime_p for primality checks

namespace bbs_production {
    mpz_class generateBlumPrime(unsigned int bitLength)
    {

        gmp_randclass gmpRand(gmp_randinit_default); // Create a random state for GMP

        std::random_device rd;
        unsigned long seedVal = ((unsigned long)rd() << 32) ^ rd();
        mpz_class seedMpz(seedVal);
        gmpRand.seed(seedMpz);

        mpz_class lowerBound = mpz_class(1) << (bitLength - 1);
        mpz_class upperBound = mpz_class(1) << bitLength;

        while(true){
            // Generate a candidate with bitLength bits

            mpz_class candidate = gmpRand.get_z_bits(bitLength);
            if (candidate < lowerBound){
                candidate += lowerBound;
            }
            if (candidate >= upperBound){
                continue;
            }

            if (candidate % 4 != 3){
                continue;
            }

            // Check probable prime

            int primeCheck = mpz_probab_prime_p(candidate.get_mpz_t(), 25);
            if (primeCheck != 0){ // 0 means composite, 1 means probably prime, 2 means definitely prime
                return candidate;
            }
        }
        
    }

    BlumBlumShub::BlumBlumShub(const mpz_class& p, const mpz_class& q, const mpz_class& seed)
        : p_(p), q_(q), n_(p*q), state_(0)
    {
        // Check if p and q are Blum primes
        if (p % 4 != 3 || q % 4 != 3){
            throw std::invalid_argument("p and q must be Blum primes");
        }

        // Check if gcd(n, seed) == 1
        mpz_class g;
        mpz_gcd(g.get_mpz_t(), seed.get_mpz_t(), n_.get_mpz_t());
        if (g != 1){
            throw std::invalid_argument("Seed is not coprime with n = p * q");
        }

        // Store seed mod n to ensure it is within [0, n)
        mpz_class seedModN;
        mpz_mod(seedModN.get_mpz_t(), seed.get_mpz_t(), n_.get_mpz_t());    
        state_ = seedModN;

    }

    unsigned int BlumBlumShub::nextBit()
    {
        // state = state^2 mod n
        mpz_class squared;
        mpz_powm_ui(squared.get_mpz_t(), state_.get_mpz_t(), 2, n_.get_mpz_t());
        state_ = squared;

        // Return the least significant bit
        unsigned long statVal = state_.get_ui();
        return static_cast<unsigned int>(statVal & 1U);
    }

    unsigned char BlumBlumShub::nextByte()
    {
        unsigned char c = 0;
        for (int i = 0; i < 8; i++)
        {
            c = (c << 1) | nextBit();
        }
        return c;
    }

    std::vector<unsigned char> BlumBlumShub::nextBytes(size_t count)
    {
        std::vector<unsigned char> output;
        for (size_t i = 0; i < count; i++)
        {
            output.push_back(nextByte());
        }
        return output;
    }
} // namespace bbs_production