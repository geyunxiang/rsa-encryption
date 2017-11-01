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

// bitLength / 8 = BigInt::values.size()
// note that bigLength should be divisible by 8
BigInt generatePrimeWithBitLength(int bitLength);

// implementation reference:
// https://langui.sh/2009/03/07/generating-very-large-primes/
bool RabinMiller(BigInt p);

bool checkIfPrime(BigInt p);

#endif /* myRSA_hpp */
