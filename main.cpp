#include <iostream>
#include <chrono>
#include <ctime>
#include <random>

#include "BigInt.h"
#include "myRSA.hpp"
#include "TestSuits.hpp"

int main(int argc, char const *argv[]) {
    BigInt a, b, c, d, p, q, s;
    
    // test this next
    // d.setValue("81C9EEF9652B102EE88DC1F637DC06DD");
    // c.setValue("DA423011A7D74976C9BDF6D28ADD0D09");
    // std::cout << "multiply result: " << (d*d).toHex() << std::endl;
    // a = (d*d)/c;
    // std::cout << "power division calculated: " << a.toHex() << std::endl;
    
    // test_checkIfPrime();
    
    // generate prime time test
    std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t ( begin );
    while((a = generatePrimeWithBitLength(768)) == ZERO_BIG_INT) ;
    std::cout << "Random prime generated: " << a.toHex() << std::endl;
    std::time_t tt2;
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    tt2 = std::chrono::system_clock::to_time_t ( today );
    std::cout << "start on: " << ctime(&tt);
    std::cout << "end   on: " << ctime(&tt2);

	// unsigned int x, y;
	// x = 143738293;
	// y = 217827364;
	// uint64_t two_digits_result = static_cast<uint64_t>(x)*static_cast<uint64_t>(y);
    // std::cout << "size of uint64t: " << sizeof(uint64_t) << std::endl;
	// unsigned int nextcarry = two_digits_result >> 32; // carry produced by multiplication
	// std::cout << "nextcarry: " << nextcarry << std::endl;
	// unsigned int digits_result = static_cast<unsigned int>(two_digits_result); // need to add with current carry
	// std::cout << "digits_result: " << digits_result << std::endl;
	// return 0;
}
