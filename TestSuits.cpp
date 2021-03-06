//
//  TestSuits.cpp
//  rsa-encryption-xcode
//
//  Created by 葛云祥 on 11/04/2017.
//  Copyright © 2017年 葛云祥. All rights reserved.
//

#include "TestSuits.hpp"
#include <iostream>

void test_hex2str() {
    std::string a("6d6563"); // mec
    std::cout << "a: " << a << std::endl;
    std::string b = hex2str(a);
    std::cout << "b: " << b << std::endl;
}

void test_str2hex() {
    std::string a("1234");
    std::cout << "a: " << a << std::endl;
    std::string b = str2hex(a);
    std::cout << "b: " << b << std::endl;
}

void test_RSAStringEncryptionDecryption() {
    MyRSAClass rsaClass(128);
    std::cout << "RSA Class built\n";
    std::cout << "RSA public key: " << rsaClass.publicKey.toHex() << std::endl;
    std::cout << "RSA private key: " << rsaClass.getPrivateKey().toHex() << std::endl;
    std::cout << "RSA modulo N: " << rsaClass.moduloN.toHex() << std::endl;
    std::cout << "RSA prime p: " << rsaClass.getP().toHex() << std::endl;
    std::cout << "RSA prime q: " << rsaClass.getQ().toHex() << std::endl;
    std::string plainText("This is another test string."), encryptedString, decryptedString;
    encryptedString = rsaClass.encryptPlainText(plainText);
    std::cout << "Encrypted string: " << encryptedString << std::endl;
    decryptedString = rsaClass.decryptCypherText(encryptedString);
    std::cout << "Decrypted string: " << decryptedString << std::endl;
}

void test_RSABigIntEncryptionDecryption() {
    MyRSAClass rsaClass(128);
    std::cout << "RSA Class built\n";
    std::cout << "RSA public key: " << rsaClass.publicKey.toHex() << std::endl;
    std::cout << "RSA private key: " << rsaClass.getPrivateKey().toHex() << std::endl;
    std::cout << "RSA modulo N: " << rsaClass.moduloN.toHex() << std::endl;
    std::cout << "RSA prime p: " << rsaClass.getP().toHex() << std::endl;
    std::cout << "RSA prime q: " << rsaClass.getQ().toHex() << std::endl;
    BigInt plain, cypher, decrypted;
    plain.setValue("1de239a79b");
    std::cout << "plain number is: " << plain.toHex() << std::endl;
    cypher = rsaClass.encryptNumber(plain);
    std::cout << "cypher number is: " << cypher.toHex() << std::endl;
    decrypted = rsaClass.decryptNumber(cypher);
    std::cout << "decrypted number is: " << decrypted.toHex() << std::endl;
}

void test_RSAConstructor() {
    std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t ( begin );
    MyRSAClass rsaEncryptor(256);
    std::time_t tt2;
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    tt2 = std::chrono::system_clock::to_time_t ( today );
    std::cout << "start on: " << ctime(&tt);
    std::cout << "end   on: " << ctime(&tt2);
}

void test_inverseModulo() {
    BigInt c, modulo, u, p, q;
    c.setValue("80495A6A30CFFCEE332A0D86AA7C0F24");
    p.setValue("E050C87B36235C2C37F6FEB828C07B53");
    q.setValue("ACF29BE8D7535494E5698B85459950DB");
    modulo = phiPrime(q, p);
    //modulo.setValue("978ADBAD3C1E1578C42C7C2DCB5492D7527A42DB2CD571A471F2D3AD16CE7001");
    u = inverseModulo(c, modulo);
    std::cout << "inverse modulo calculated as: " << u.toHex() << std::endl;
}

void test_inverseModuloInt() {
    int result = inverseModulo(4, 11);
    std::cout << "inverse modulo calculated as: " << result << std::endl;
}

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
    a.setValue("3");
    b.setValue("4");
    b.reverseSign();
    c = a + b;
    std::cout << "addition result: " << c.toHex() << std::endl;
}

void test_minusOperator() {
    BigInt a, b, c;
    a.setValue("0");
    b.setValue("3");
    //b.reverseSign();
    c = a - b;
    std::cout << "submission result: " << c.toHex() << std::endl;
}

void test_multiplicationOperator() {
    BigInt a, b, c;
    a.setValue("E050C87B36235C2C37F6FEB828C07B53");
    b.setValue("ACF29BE8D7535494E5698B85459950DB");
    c = a * b;
    std::cout << "multiplication result: " << c.toHex() << std::endl;
    b.reverseSign();
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
    c.setValue("401");
    std::cout << "comparison result: " << std::boolalpha << (a < b) << std::endl;
    std::cout << "comparison result: " << std::boolalpha << (a < c) << std::endl;
    //std::cout << "a.length: " << a.getLength() << "  c.length: " << c.getLength() << std::endl;
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
