#ifndef BBS_TOY_HPP
#define BBS_TOY_HPP

#include <vector>

namespace bbs_toy {
    // Basic Blum-Blum-Shub demo class
    // Uses small 64-bit integers for p and q
    // Uses naive prime checks for demonstration purposes
    class BlumBlumShub{
    public:
        // Constructor takes primes p and q, and the seed 
        BlumBlumShub(unsigned long p, unsigned long q, unsigned long seed);

        // Generates next bit
        unsigned int nextBit();
        
        // Generates next byte
        unsigned char nextByte();

        // Generates count bytes
        std::vector<unsigned char> nextBytes(size_t count);

        unsigned long getP() const {return p_;}
        unsigned long getQ() const {return q_;}
        unsigned long getN() const {return n_;}
        unsigned long getState() const {return state_;}

    private:
        unsigned long p_;
        unsigned long q_;
        unsigned long n_; // n = p*q
        unsigned long state_;

    };


// Naive prime check function
bool isPrime(unsigned long n);

// Generates a Blum prime p within [lower, upper] s.t p % 4 == 3
unsigned long generateBlumPrime(unsigned long lower, unsigned long upper);
}

#endif // BBS_TOY_HPP