#include "bbs_toy.hpp"
#include <random>
#include <cmath>    

namespace bbs_toy
{
    bool isPrime(unsigned long n)
    {
        if (n <= 1)
            return false;
        if (n == 2)
            return true;
        if (n % 2 == 0)
            return false;

        unsigned long limit = static_cast<unsigned long>(std::sqrt((long double)n));

        for (unsigned long i = 3; i < limit; i += 2)
        {
            if (n % i == 0) {return false;}
                
        }
        return true;
    }
    
    unsigned long generateBlumPrime(unsigned long lower, unsigned long upper)
    {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<unsigned long> dist(lower, upper);

        while (true)
        {
            unsigned long candidate = dist(rng);
            if (isPrime(candidate) && candidate % 4 == 3)
            {
                return candidate;
            }
        }
    }

    BlumBlumShub::BlumBlumShub(unsigned long p, unsigned long q, unsigned long seed)
        : p_(p), q_(q), n_(p*q), state_(seed)
    {
        // Check if p and q are Blum primes
        // Check if gcd(n, seed) == 1
    }

    unsigned int BlumBlumShub::nextBit()
    {
        // x_{i+1} = x_i^2 mod n
        unsigned long long sq = (unsigned long long)state_ * (unsigned long long)state_;
        state_ = static_cast<unsigned long>(sq % n_);
        return static_cast<unsigned int>(state_ & 1U);
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
        std::vector<unsigned char> out;
        out.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            out.push_back(nextByte());
        }
        return out;
    }
} // namespace bbs_toy
