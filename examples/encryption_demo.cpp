#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include "bbs_production.hpp"


// Encryption function
std::vector<unsigned char> encrypt(const std::string &plaintext, bbs_production::BlumBlumShub& bbs){
    std::vector<unsigned char> ciphertext;
    ciphertext.reserve(plaintext.size());
    for (unsigned char ch : plaintext){
        unsigned char keystream_byte = bbs.nextByte();
        ciphertext.push_back(ch ^ keystream_byte);
    }
    return ciphertext;
}

//Decryption function
std::string decrypt(const std::vector<unsigned char> &ciphertext, bbs_production::BlumBlumShub& bbs){
    std::string plaintext;
    plaintext.reserve(ciphertext.size());
    for (unsigned char ch : ciphertext){
        unsigned char keystream_byte = bbs.nextByte();
        plaintext.push_back(ch ^ keystream_byte);
    }
    return plaintext;
}

int main(){
    using namespace bbs_production;

    // Generate Blum primes p and q of a certain bit length
    unsigned int bitLength = 512;

    std::cout << "Encryption with Blum-Blum-Shub demo" << std::endl;
    std::cout << "Generating Blum primes p and q with bit length ...\n" << bitLength << std::endl;

    mpz_class p = generateBlumPrime(bitLength);
    mpz_class q = generateBlumPrime(bitLength);

    mpz_class n = p * q;
    std::cout << "p bit length = " << mpz_sizeinbase(p.get_mpz_t(), 2) << std::endl;
    std::cout << "q bit length = " << mpz_sizeinbase(q.get_mpz_t(), 2) << std::endl;
    std::cout << "n bit length = " << mpz_sizeinbase(n.get_mpz_t(), 2) << std::endl;

    mpz_class seedCandidate(123456789);

    BlumBlumShub bbs(p, q, seedCandidate);

    std::string message = "Hello, world! This is a secret message.";

    std::cout << "Original Message: " << message << "\n";

    std::vector<unsigned char> ciphertext = encrypt(message, bbs);

    std::cout << "Ciphertext (hex): ";
    for (auto b : ciphertext){
        std::printf("%02x", b);
    }
    std::cout << "\n";

    BlumBlumShub bbsDecrpt(p, q, seedCandidate);

    std::string decrypted = decrypt(ciphertext, bbsDecrpt);
    std::cout << "Decrypted Message: " << decrypted << std::endl;

    return 0;
}