//
//  myRSA.hpp
//  rsa-encryption-xcode
//
//  Created by 葛云祥 on 11/01/2017.
//  Copyright © 2017年 葛云祥. All rights reserved.
//

#ifndef myRSA_hpp
#define myRSA_hpp

#include <iostream>
#include "BigInt.h"

// two primes, p, q
//   -> one public key n = pq
// calculate phi(n) = (p-1)*(q-1)
//   -> choose public key e, gcd(e, phi(n)) == 1
// calculate d = e^-1 modulo phi(n), i.e. d*e = 1 modulo phi(n)
//   -> private key is d
class MyRSAClass {
public:
    BigInt publicKey;
    BigInt moduloN;
    MyRSAClass(int keyBitLength); // initialize with the specified bit-length key
    MyRSAClass(std::string publicKeyStr, std::string moduloNStr); // initialize with public key and str for encryption
    MyRSAClass(std::string publicKeyStr, std::string moduloNStr, std::string privateKeyStr);
    void regenerateKeyPairsWithBitLength(int keyBitLength);
    BigInt encryptNumber(BigInt plain);
    BigInt decryptNumber(BigInt cypher);
    std::string encryptPlainText(std::string plainText);
    std::string decryptCypherText(std::string cypherText);
    BigInt getPrivateKey(); // for debug usage only
private:
    BigInt privateKey;
    BigInt p; // big prime used to calculate moduloN
    BigInt q;
};

// calculate the inverse of e with the specified modulo
BigInt inverseModulo(BigInt e, BigInt modulo);
int inverseModulo(int c, int modulo);

// calculate phi(pq) where p and q are primes
BigInt phiPrime(BigInt p, BigInt q);

// Primality check and generate prime function
// implementation reference:
// https://langui.sh/2009/03/07/generating-very-large-primes/
bool RabinMiller(BigInt p);

bool checkIfPrime(BigInt p);

// bitLength / 8 = BigInt::values.size()
// note that bigLength should be divisible by 8
BigInt generatePrimeWithBitLength(int bitLength);

// search linearly
BigInt generateOrderedPrime(int bitLength);

// helper function
void listLowPrimes();

#endif /* myRSA_hpp */
