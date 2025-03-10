#ifndef BBS_SIDECHANNEL_HPP
#define BBS_SIDECHANNEL_HPP

#include <vector>

// Toy Blum-Blum-Shub generator that simulates side-channel leakage
// Side channel leakage refers to information that is unintentionally leaked by the implementation
// ToySideChannelBBS works like our standard Toy BBS, but if the generated bit is 1, 
// it deliberately performs extra dummy computations to add a measurable delay.
// This is for demonstration purposes only.

namespace bbs_sidechannel {
class ToySideChannelBBS{
public:
    ToySideChannelBBS(unsigned long p, unsigned long q, unsigned long seed);
    unsigned int nextBit();
    unsigned char nextByte();
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

};  // namespace bbs_sidechannel

#endif // BBS_SIDECHANNEL_HPP






}