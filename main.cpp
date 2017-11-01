#include <iostream>
#include "BigInt.h"
#include "myRSA.hpp"


// currently can generate prime with max bit length 64
// need to speed up power calculation
// also need to adjust random number generating method
int main(int argc, char const *argv[]) {
    BigInt a, b, c, d, p, q, s;
    // b = BigInt(32);
    // a = pow(TWO_BIG_INT, b);
    //std::cout << "power calculated: " << a.toHex() << std::endl;
    
    // a = generateOrderedPrime(16);
    while((a = generatePrimeWithBitLength(64)) == ZERO_BIG_INT) ;
    std::cout << "Random prime generated: " << a.toHex() << std::endl;
    // listLowPrimes();
    // a.setValue("269");
    // std::cout << "prime test result: " << std::boolalpha << checkIfPrime(a) << std::endl;
    // std::cout << "Rabin Miller result: " << std::boolalpha << RabinMiller(a) << std::endl;

    // a.setValue("2");
    // b.setValue("40ce34520");
    // c = getRandom(a, b);
    // c = getRandom(a, b);
    // c = getRandom(a, b);
    // std::cout << "random number: " << c.toHex() << std::endl;
    
	// p.setValue("1a2b345645cd78634a8298b6aefd3412354dfe78a9"); // 76498
	// std::cout << "p equals " << p.toHex() << std::endl;
	// q.setValue("f8d79fe893eb2ec8"); // 34623
	// std::cout << "q equals " << q.toHex() << std::endl;
	// // s.put(34);
	// BigInt r = p / q;
	// std::cout << "quotion equals " << r.toHex() << std::endl;

	// a.setValue("234534");
	// b.setValue("abcdef1234");
	// c = a + b;
	// std::cout << "addition result: " << c.toHex() << std::endl;

	// a.setValue("1000000000");
	// b.setValue("fffffffff");
	// c = a - b;
	// std::cout << "submission result: " << c.toHex() << std::endl;

	// a.setValue("10");
	// b.setValue("40");
	// c = a * b;
	// std::cout << "multiplication result: " << c.toHex() << std::endl;

	// a.setValue("400");
	// b.setValue("10");
	// c.setValue("40");
	// d = b*c;
	// // std::cout << "comparison result: " << std::boolalpha << (a == (b*c)) << std::endl;
	// std::cout << "comparison result: " << std::boolalpha << (a == d) << std::endl;
	// std::cout << "a.length: " << a.getLength() << "  d.length: " << d.getLength() << std::endl;

	// a.setValue("400");
	// b.setValue("11");
	// c = a / b;
	// std::cout << "dividen result: " << c.toHex() << std::endl;

	// byte a, b, c;
	// a = 143;
	// b = 217;
	// byte currentcarry = 0;
	// unsigned short two_digits_result = static_cast<unsigned short>(a)*static_cast<unsigned short>(b);
	// two_digits_result += currentcarry;
	// byte nextcarry = two_digits_result >> 8; // carry produced by multiplication
	// std::cout << "nextcarry: " << static_cast<int>(nextcarry) << std::endl;
	// byte digits_result = two_digits_result; // need to add with current carry
	// std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
	// currentcarry = nextcarry;
	// byte split[2];
	// split[0] = (a << 4);
	// split[0] = split[0] >> 4;
	// split[1] = (a >> 4) << 4; // works 
	// std::cout << "split[0]: " << static_cast<int>(split[0]) << std::endl;
	// std::cout << "split[1]: " << static_cast<int>(split[1]) << std::endl;
	// std::cout << "c: " << static_cast<int>(c) << std::endl;
	return 0;
}
