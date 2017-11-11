//
//  TestSuits.hpp
//  rsa-encryption-xcode
//
//  Created by 葛云祥 on 11/04/2017.
//  Copyright © 2017年 葛云祥. All rights reserved.
//

#ifndef TestSuits_hpp
#define TestSuits_hpp

#include "BigInt.h"
#include "myRSA.hpp"

void test_RSABigIntEncryptionDecryption();
void test_RSAConstructor();
void test_inverseModulo();
void test_inverseModuloInt();
void test_increaseOne();
void test_setValueString();
void test_setValueInt();
void test_additionOperator();
void test_minusOperator();
void test_multiplicationOperator();
void test_divisionOperator();
void test_moduloOperator();
void test_comparisionOperator();
void test_pow();
void test_powModulo();
void test_checkIfPrime();
void test_getRandom();

#endif /* TestSuits_hpp */
