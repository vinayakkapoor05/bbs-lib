#include <iostream>
#include <vector>
#include <cstdio>
#include <bbs_production.hpp>

int main(){

    using namespace bbs_production;

    // Generate Blum primes p and q of a certain bit length
    unsigned int bitLength = 512;

    std::cout << "Production Blum-Blum-Shub demo" << std::endl;
    std::cout << "Generating Blum primes p and q with bit length ...\n" << bitLength << std::endl;

    mpz_class p = generateBlumPrime(bitLength);
    mpz_class q = generateBlumPrime(bitLength);

    mpz_class n = p * q;
    std::cout << "p bit length = " << mpz_sizeinbase(p.get_mpz_t(), 2) << std::endl;
    std::cout << "q bit length = " << mpz_sizeinbase(q.get_mpz_t(), 2) << std::endl;
    std::cout << "n bit length = " << mpz_sizeinbase(n.get_mpz_t(), 2) << std::endl;

    std::cout << "p = " << p << std::endl;
    std::cout << "q = " << q << std::endl;
    std::cout << "n = p*q = " << n << std::endl;

    // Choose a seed
    gmp_randclass gmpRand(gmp_randinit_default);
    gmpRand.seed(12345UL);

    mpz_class seedCandidate;

    while(true){
        seedCandidate = gmpRand.get_z_bits(bitLength * 2);

        // gcd(seed, n) == 1
        mpz_class g;
        mpz_gcd(g.get_mpz_t(), seedCandidate.get_mpz_t(), n.get_mpz_t());
        if (g == 1){
            break;
        }

    }

    BlumBlumShub bbs(p, q, seedCandidate);

    std::cout << "16 random bytes: ";
    auto randomBytes = bbs.nextBytes(16);

    for (auto b : randomBytes){
        std::printf("%02x", b);
    }
    std::cout << "\n";

    return 0;

    
}