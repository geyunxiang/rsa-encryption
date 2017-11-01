//
//  myRSA.cpp
//  rsa-encryption-xcode
//
//  Created by 葛云祥 on 11/01/2017.
//  Copyright © 2017年 葛云祥. All rights reserved.
//

#include "myRSA.hpp"
#include <iostream>

#define DEBUG true

bool RabinMiller(BigInt p) {
    BigInt s = p - ONE_BIG_INT;
    BigInt t(0);
    const BigInt TWO(2);
    while(s % TWO == ZERO_BIG_INT) {
        s = s / TWO;
        t = t + ONE_BIG_INT;
    }
    for(int k = 0; k < 8; k++) {
        if(DEBUG) std::cout << "rabin miller try: " << k << std::endl;
        BigInt a = getRandom(TWO, p-ONE_BIG_INT);
        BigInt v = pow(a, s) % p;
        if(v != ONE_BIG_INT) {
            BigInt i(0);
            while(v != (p-ONE_BIG_INT)) {
                if(i == t-ONE_BIG_INT)
                    return false;
                else {
                    i = i + ONE_BIG_INT;
                    v = (v*v) % p;
                }
            }
        }
    }
    return true;
}

int lowPrimes[] = {3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997};

bool checkIfPrime(BigInt p) {
    if(p % TWO_BIG_INT == 0) return false;
    // for n in lowPrimes, if n == p return True; if n%p == 0 return false
    return RabinMiller(p);
}



BigInt generatePrimeWithBitLength(int bitLength) {
    BigInt result(0);
    BigInt randInt;
    int r = 100; // try 100 times
    for(r = 100; r > 0; r--) {
        if(DEBUG) std::cout << "generate prime left try: " << r << std::endl;
        randInt = getRandom(pow(TWO_BIG_INT, BigInt(bitLength-1)), pow(TWO_BIG_INT, BigInt(bitLength)));
        if(checkIfPrime(randInt)) return randInt;
    }
    return result;
}
