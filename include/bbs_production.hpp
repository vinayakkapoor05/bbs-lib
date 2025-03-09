#ifndef BBS_PRODUCTION_HPP
#define BBS_PRODUCTION_HPP

#include <vector>
#include <gmpxx.h>

namespace bbs_production{
mpz_class generateBlumPrime(unsigned int bitLength);
class BlumBlumShub{
public:

    BlumBlumShub(const mpz_class& p, const mpz_class& q, const mpz_class& seed);
    unsigned int nextBit();
    unsigned char nextByte();
    std::vector<unsigned char> nextBytes(size_t count);

    const mpz_class getP() const {return p_;};
    const mpz_class getQ() const {return q_;};
    const mpz_class getN() const {return n_;};
    const mpz_class getState() const {return state_;};

private:
        mpz_class p_; 
        mpz_class q_;
        mpz_class n_; // n = p*q
        mpz_class state_;
};


} // namespace bbs_production

#endif // BBS_PRODUCTION_HPP