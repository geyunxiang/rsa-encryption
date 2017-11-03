#include <iostream>
#include "BigInt.h"
#include "myRSA.hpp"
#include <chrono>
#include <ctime>
#include <random>

// currently can generate prime with max bit length 64
// need to speed up power calculation
// also need to adjust random number generating method
int main(int argc, char const *argv[]) {
    BigInt a, b, c, d, p, q, s;
    
    //a.setValue("2FFFFFFFF");
    //a.increaseOne();
    //std::cout << "a equals: " << a.toHex() << std::endl;
    
    //a.setValue("FFFFFFFFFFFFF");
    //std::cout << "a equals: " << a.toHex() << std::endl;
    
    //a.setValue(2847293);
    //std::cout << "a equals: " << a.toHex() << std::endl;

    // a.setValue("4668442");
    // b.setValue("AB2");
    // c = a % b;
    // std::cout << "modulo calculated: " << c.toHex() << std::endl;
    
    //d.setValue(2);
    //c.setValue(32);
    //std::cout << "power calculated: " << pow(d, c).toHex() << std::endl;
    
    
	// a.setValue("1C34F076569D6A0E6F842299AC343D06C5999945");
	// b.setValue("1C34F076D6319132FE4FB6511404FF64E354D60E");
	// c = a - b;
	// std::cout << "submission result: " << c.toHex() << std::endl;
    
    // test this next
    // d.setValue("81C9EEF9652B102EE88DC1F637DC06DD");
    // c.setValue("DA423011A7D74976C9BDF6D28ADD0D09");
    // std::cout << "multiply result: " << (d*d).toHex() << std::endl;
    // a = (d*d)/c;
    // std::cout << "power division calculated: " << a.toHex() << std::endl;
    
    // d.setValue("87AD3D06606BD9");
    // b.setValue("1B48460234FAE92ED937BEDA515BA1A1");
    // c.setValue("DA423011A7D74976C9BDF6D28ADD0D09");
    // std::cout << "d: " << d.toHex() << std::endl;
    // std::cout << "b: " << b.toHex() << std::endl;
    // std::cout << "c: " << c.toHex() << std::endl;
    // a = pow(d, b, c); // ans 6489059523318327863115348632635531620, 4E1BF55E9DF832062A6AD6BC00D6164
    // std::cout << "power modulo calculated: " << a.toHex() << std::endl;
    
    
    //a.setValue("F1603517446C8E8365324DC981F1B064B6FC4003D5817A6EA64FE22374FD2E83");
    //std::cout << "prime test result: " << std::boolalpha << checkIfPrime(a) << std::endl;
    
    std::chrono::system_clock::time_point begin = std::chrono::system_clock::now();
    std::time_t tt;
    tt = std::chrono::system_clock::to_time_t ( begin );
    
    while((a = generatePrimeWithBitLength(256)) == ZERO_BIG_INT) ;
    std::cout << "Random prime generated: " << a.toHex() << std::endl;
    std::time_t tt2;
    std::chrono::system_clock::time_point today = std::chrono::system_clock::now();
    tt2 = std::chrono::system_clock::to_time_t ( today );
    std::cout << "start on: " << ctime(&tt);
    std::cout << "end   on: " << ctime(&tt2);
    

    // a.setValue("2");
    // b.setValue("40ce34520");
    // c = getRandom(a, b);
    // c = getRandom(a, b);
    // c = getRandom(a, b);
    // std::cout << "random number: " << c.toHex() << std::endl;
    
	// p.setValue("1292F44D0E94BEE");
	// std::cout << "p equals " << p.toHex() << std::endl;
	// q.setValue("118FA76E");
	// std::cout << "q equals " << q.toHex() << std::endl;
	// BigInt r = p / q;
	// std::cout << "quotion equals " << r.toHex() << std::endl;

	// a.setValue("234534");
	// b.setValue("abcdef1234");
	// c = a + b;
	// std::cout << "addition result: " << c.toHex() << std::endl;

	// a.setValue(283918273);
	// b.setValue(294627182);
	// c = a * b;
	// std::cout << "multiplication result: " << c.toHex() << std::endl;

	// a.setValue("400");
	// b.setValue("10");
	// c.setValue("40");
	// d = b*c;
	// // std::cout << "comparison result: " << std::boolalpha << (a == (b*c)) << std::endl;
	// std::cout << "comparison result: " << std::boolalpha << (a == d) << std::endl;
	// std::cout << "a.length: " << a.getLength() << "  d.length: " << d.getLength() << std::endl;

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
