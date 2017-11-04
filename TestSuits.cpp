//
//  TestSuits.cpp
//  rsa-encryption-xcode
//
//  Created by 葛云祥 on 11/04/2017.
//  Copyright © 2017年 葛云祥. All rights reserved.
//

#include "TestSuits.hpp"
#include <iostream>

void test_increaseOne() {
    BigInt a;
    a.setValue("2FFFFFFFF");
    a.increaseOne();
    std::cout << "a equals: " << a.toHex() << std::endl;
}

void test_setValueString() {
    BigInt a;
    a.setValue("FFFFFFFFFFFFF");
    std::cout << "a equals: " << a.toHex() << std::endl;

}

void test_setValueInt() {
    BigInt a;
    a.setValue(2847293);
    std::cout << "a equals: " << a.toHex() << std::endl;

}

void test_additionOperator() {
    BigInt a, b, c;
    a.setValue("234534");
    b.setValue("abcdef1234");
    c = a + b;
    std::cout << "addition result: " << c.toHex() << std::endl;
}

void test_minusOperator() {
    BigInt a, b, c;
    a.setValue("1C34F076569D6A0E6F842299AC343D06C5999945");
    b.setValue("1C34F076D6319132FE4FB6511404FF64E354D60E");
    c = a - b;
    std::cout << "submission result: " << c.toHex() << std::endl;
}

void test_multiplicationOperator() {
    BigInt a, b, c;
    a.setValue(283918273);
    b.setValue(294627182);
    c = a * b;
    std::cout << "multiplication result: " << c.toHex() << std::endl;
}

void test_divisionOperator() {
    BigInt a, b, c;
    a.setValue("1292F44D0E94BEE");
    b.setValue("118FA76E");
    c = a / b;
    std::cout << "quotion equals " << c.toHex() << std::endl;
}

void test_moduloOperator() {
    BigInt a, b, c;
    a.setValue("4668442");
    b.setValue("AB2");
    c = a % b;
    std::cout << "modulo calculated: " << c.toHex() << std::endl;
}

void test_comparisionOperator() {
    BigInt a, b, c, d;
    a.setValue("400");
    b.setValue("10");
    c.setValue("40");
    d = b*c;
    std::cout << "comparison result: " << std::boolalpha << (a == (b*c)) << std::endl;
    std::cout << "comparison result: " << std::boolalpha << (a == d) << std::endl;
    std::cout << "a.length: " << a.getLength() << "  d.length: " << d.getLength() << std::endl;
}

void test_pow() {
    BigInt a, b;
    a.setValue(2);
    b.setValue(32);
    std::cout << "power calculated: " << pow(a, b).toHex() << std::endl;
}

void test_powModulo() {
    BigInt a, b, c, d;
    d.setValue("87AD3D06606BD9");
    b.setValue("1B48460234FAE92ED937BEDA515BA1A1");
    c.setValue("DA423011A7D74976C9BDF6D28ADD0D09");
    std::cout << "d: " << d.toHex() << std::endl;
    std::cout << "b: " << b.toHex() << std::endl;
    std::cout << "c: " << c.toHex() << std::endl;
    a = pow(d, b, c); // ans 6489059523318327863115348632635531620, 4E1BF55E9DF832062A6AD6BC00D6164
    std::cout << "power modulo calculated: " << a.toHex() << std::endl;
}

void test_checkIfPrime() {
    BigInt a;
    a.setValue("F1603517446C8E8365324DC981F1B064B6FC4003D5817A6EA64FE22374FD2E83");
    std::cout << "prime test result: " << std::boolalpha << checkIfPrime(a) << std::endl;
}

void test_getRandom() {
    BigInt a, b, c;
    a.setValue("2");
    b.setValue("40ce34520");
    c = getRandom(a, b);
    std::cout << "random number: " << c.toHex() << std::endl;
}
