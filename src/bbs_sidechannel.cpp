#include "bbs_sidechannel.hpp"
#include <cmath>
#include <thread>

namespace bbs_sidechannel {



    ToySideChannelBBS::ToySideChannelBBS(unsigned long p, unsigned long q, unsigned long seed)
        : p_(p), q_(q), n_(p*q), state_(seed)
    {
        // Assume p and q are Blum primes
        // Assume seed is coprime with n = p * q
        // Check if p and q are Blum primes
       
    }

    unsigned int ToySideChannelBBS::nextBit()
    {
        // state = state^2 mod n
        unsigned long long sq = (unsigned long long)state_ * (unsigned long long)state_;
        state_ = static_cast<unsigned long>(sq % n_);

        unsigned int bit = state_ & 1U;

        // Simulate side-channel leakage

        if (bit == 1){
            volatile unsigned long dummy = 0;
            // Busy loop to add a delay

            for (int i = 0; i < 10000; i++){
                dummy += i;
            }
        }

        return bit;
    }

    unsigned char ToySideChannelBBS::nextByte()
    {
        unsigned char c = 0;
        for (int i = 0; i < 8; i++)
        {
            c = (c << 1) | nextBit();
        }
        return c;
    }

    std::vector<unsigned char> ToySideChannelBBS::nextBytes(size_t count)
    {
        std::vector<unsigned char> bytes;
        bytes.reserve(count);
        for (size_t i = 0; i < count; i++)
        {
            bytes.push_back(nextByte());
        }
        return bytes;
    
    }
} // namespace bbs_sidechannel