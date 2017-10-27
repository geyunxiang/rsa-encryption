#include <iostream>
#include "BigInt.h"

int main(int argc, char const *argv[]) {
	BigInt p, q, s;
	p.setValue("873F"); // 2876
	std::cout << "p equals " << p.toHex() << std::endl;
	q.setValue("12AD2"); // 3547
	std::cout << "q equals " << q.toHex() << std::endl;
	// s.put(34);
	BigInt r = q * p;
	std::cout << r.toHex() << std::endl;
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