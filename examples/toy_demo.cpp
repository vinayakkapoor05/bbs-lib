#include <iostream>
#include <vector>
#include <cstdio>  
#include <bbs_toy.hpp>

int main()
{
    unsigned long p = bbs_toy::generateBlumPrime(10000, 20000);
    unsigned long q = bbs_toy::generateBlumPrime(20000, 30000);

    unsigned long seed = 12345;

    bbs_toy::BlumBlumShub bbs(p, q, seed);

    std::cout << "Toy Blum-Blum-Shub demo" << std::endl;
    std::cout << "p = " << bbs.getP() << std::endl;
    std::cout << "q = " << bbs.getQ() << std::endl;
    std::cout << "n = p*q = " << bbs.getN() << std::endl;
    std::cout << "seed = " << seed << std::endl;


    std::cout << "\n\n";
    std::cout << "10 random bytes: ";
    auto bytes = bbs.nextBytes(10);
    for (auto b : bytes)
    {
        std::printf("%02x", b);
    }
    std::cout << "\n";

    return 0;
}
