#include "BigInt.h"
#include <algorithm>
#include <sstream>
#include <chrono>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#define DEBUG false

const int RESERVED_LENGTH = 1000;

// constructor
BigInt::BigInt() {
    values.reserve(RESERVED_LENGTH);
}

BigInt::BigInt(unsigned int a) {
    values.reserve(RESERVED_LENGTH);
    values.push_back(a);
}

// Helper functions
// not tested
std::string BigInt::toHex() {
	char converted[values.size()*2+1];
	for(int i = 0; i < values.size(); i++) {
		sprintf(&converted[i*2], "%02X", static_cast<int>(values.at(values.size() - i - 1)));
	}
	return std::string(converted);
}

// get the length of this bigint
int BigInt::getLength() const {
	return static_cast<int>(values.size());
}

// get the specific byte value
unsigned int BigInt::get(int index) const {
	return values.at(index);
}

// put value to the rear
void BigInt::put(unsigned int value) {
	values.push_back(value);
}

// insert zeros to the lowest pos
void BigInt::insertZeros(int num) {
	for(int i = 0; i < num; i ++) {
		values.insert(values.begin(), 0);
	}
}

// insert byte value to the lowest pos
void BigInt::insert(unsigned int value) {
	if(values.size() == 1 && values.at(0) == 0) values[0] = value;
	else values.insert(values.begin(), value);
}

// make the bigint have value
void BigInt::setValue(unsigned int value) {
	values = std::vector<unsigned int> (1, value);
    values.reserve(RESERVED_LENGTH);
}

// init BigInt from string or reset its value
// not tested
void BigInt::setValue(std::string value) {
	unsigned int buf;
	values = std::vector<unsigned int>();
	for(int i = static_cast<int>(value.size()) - 2; i >= 0; i -= 2) {
		std::stringstream ss;
		ss << std::hex << value.substr(i, 2);
		ss >> buf;
		values.push_back(static_cast<byte>(buf));
		ss.str("");
	}
	if(value.size() % 2 == 1) {
		std::stringstream ss;
		ss << std::hex << value.at(0);
		ss >> buf;
		values.push_back(static_cast<byte>(buf));
	}
	this->trim();
    values.reserve(RESERVED_LENGTH);
}

// Four basic operations
BigInt operator+(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	byte carry = 0, op1, op2, digits_result;
	for(int count = 0; count < std::max(lop.getLength(), rop.getLength()); count ++) {
		op1 = count < lop.getLength() ? lop.get(count) : 0;
		op2 = count < rop.getLength() ? rop.get(count) : 0;
		digits_result = op1 + op2 + carry;
		if (digits_result - carry < std::max(op1, op2)) {
			carry = 1;
			//if(DEBUG) std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
			//if(DEBUG) std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
		} else {
			carry = 0;
		}
		result.put(digits_result);
	}
	if(carry != 0) 
		result.put(carry);
	return result;
}

BigInt operator-(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	byte carry = 0, op1, op2, digits_result;
	if(lop.getLength() < rop.getLength()) {
		result.setValue(0);
		return result;
	}
	int count;
	for(count = 0; count < rop.getLength(); count ++) {
		op1 = lop.get(count);
		op2 = rop.get(count);
		digits_result = op1 - op2 - carry;
		if(digits_result + carry > op1) {
			carry = 1;
		} else {
			carry = 0;
		}
		result.put(digits_result);
	}
	while(count < lop.getLength()) {
		op1 = lop.get(count);
		digits_result = op1 - carry;
		if(digits_result > op1) {
			carry = 1;
		} else {
			carry = 0;
		}
		result.put(digits_result);
		count ++;
	}
	if(carry == 1) result.setValue(0);
	result.trim();
	return result;
}

// rop only contains one digit
BigInt multiplyOneDigit(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	byte op2 = rop.get(0);
	byte carry = 0;
	for(int count = 0; count < lop.getLength(); count ++) {
		byte op1 = lop.get(count);
		unsigned short two_digits_result = static_cast<unsigned short>(op1)*static_cast<unsigned short>(op2);
		two_digits_result += carry;
		carry = two_digits_result >> 8; // carry
		//if(DEBUG) std::cout << "new carry: " << static_cast<int>(carry) << std::endl;
		byte digits_result = two_digits_result; // lower 8 bit
		result.put(digits_result);
	}
	if(carry != 0) {
		result.put(carry);
	}
	return result;
}

BigInt operator*(const BigInt& lop, const BigInt& rop) {
	BigInt result(0);
	for(int count = 0; count < rop.getLength(); count ++) {
		BigInt posresult;
		BigInt singlerop;
		singlerop.put(rop.get(count));
		posresult = multiplyOneDigit(lop, singlerop);
		posresult.insertZeros(count);
		posresult.trim();
		result = result + posresult;
	}
	return result;
}

byte divideResult(const BigInt& dividen, const BigInt& divider) {
	// this should return a value less than 255
	byte result = 0;
    BigInt multResult(0);
	while(true) {
		result ++;
        multResult = multResult + divider;
		//quotion.setValue(result);
		if(dividen == multResult) return result;
		if(dividen - multResult < divider) {
			return result;
		}
		if(result == 255) return result;
	}
}

BigInt operator/(const BigInt& lop, const BigInt& divider) {
	BigInt result;
	if(lop < divider) {
		result.setValue(0);
		return result;
	}
	BigInt dividen(0);
    BigInt quotInt(0);
	for(int i = lop.getLength() - 1; i >= 0; i--) {
		dividen.insert(lop.get(i));
		if(dividen < divider) {
			result.insertZeros(1);
		} else if(dividen == divider) {
			result.insert(1);
			dividen.setValue(0);
		} else {
			// dividen > divider but their size equals
			byte quot = divideResult(dividen, divider);
			quotInt.setValue(quot);
			result.insert(quot);
			dividen = dividen - multiplyOneDigit(divider, quotInt);
		}
	}
	result.trim();
	return result;
}

BigInt operator%(const BigInt& lop, const BigInt& divider) {
	//return lop-(lop/divider)*divider;
    if(lop < divider) {
        return lop;
    }
    BigInt dividen(0);
    for(int i = lop.getLength() - 1; i >= 0; i--) {
        dividen.insert(lop.get(i));
        if(dividen == divider) {
            dividen.setValue(0);
        } else if(dividen > divider) {
            // dividen > divider but their size equals
            byte quot = divideResult(dividen, divider);
            BigInt quotInt(quot);
            dividen = dividen - multiplyOneDigit(divider, quotInt);
        }
    }
    dividen.trim();
    return dividen;
}

BigInt operator++(const BigInt& lop) {
    BigInt rop;
    rop.setValue("1");
    return lop+rop;
}

// Comparisons
bool operator== (const BigInt& lop, const BigInt& rop) {
	if(lop.getLength() != rop.getLength()) return false;
	for(int i = 0; i < lop.getLength(); i++) {
		if(lop.get(i) != rop.get(i)) return false;
	}
	return true;
}

bool operator!= (const BigInt& lop, const BigInt& rop) {return !(lop==rop);}

bool operator< (const BigInt& lop, const BigInt& rop) {
	if(lop.getLength() < rop.getLength()) {
		return true;
	} else if(lop.getLength() > rop.getLength()) {
		return false;
	} else {
		// length equals
		if(rop - lop == ZERO_BIG_INT) return false;
		else return true;
	}
}

bool operator<= (const BigInt& lop, const BigInt& rop) {
    return lop < rop || lop == rop;
}

bool operator> (const BigInt& lop, const BigInt& rop) {
	return rop < lop;
}

bool operator>= (const BigInt& lop, const BigInt& rop) {
    return lop > rop || lop == rop;
}

// Other functions
BigInt pow(BigInt base, BigInt power) {
    BigInt result;
    result.setValue("1");
    BigInt counter;
    BigInt one;
    one.setValue("1");
    for(counter.setValue("0"); counter < power; counter = counter + one){
        result = result * base;
    }
    return result;
}

BigInt pow(BigInt base, BigInt power, BigInt modulo) {
    BigInt powModuloResult[256]; // base^(2^i) % modulo = powModuloResult[i]
    powModuloResult[0] = base % modulo; // base^(2^0) = base^1 = base % modulo
    for(int i = 1; i < 256; i++) {
        BigInt multResult = powModuloResult[i-1] * powModuloResult[i-1];
        //std::cout << "multiplied" << std::endl;
        powModuloResult[i] = (multResult) % modulo;
        //std::cout << "modulo calculated" << std::endl;
    }
    std::cout << "powModule list built" << std::endl;
    BigInt result(1);
    BigInt powerLeft = power;
    for(int i = 255; i >= 0; i--) {
        BigInt tmp = pow(TWO_BIG_INT, BigInt(i));
        while(true) {
            if(powerLeft < tmp) break;
            result = result * powModuloResult[i] % modulo;
            powerLeft = powerLeft - pow(TWO_BIG_INT, BigInt(i));
        }
        //std::cout << "powerLeft: " << powerLeft.toHex() << std::endl;
    }
    std::cout << "powerLeft: " << powerLeft.toHex() << std::endl;
    return result;
}

BigInt getRandomWithBitLength(int bitLength) {
    int vectorLength = bitLength / 8;
    BigInt result;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    for(int i = 0; i < vectorLength; i++)
        result.put(static_cast<byte>(generator()%256));
    return result;
}

BigInt getRandom(BigInt lowerbound, BigInt upperbound) {
    BigInt result;
    int lowerLength = lowerbound.getLength(), upperLength = upperbound.getLength();
    int lengthGap = upperLength - lowerLength;
    int randGap = 0;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);
    while (true) {
        randGap = lengthGap == 0 ? 0 : generator() % lengthGap;
        result = getRandomWithBitLength((lowerLength+randGap)*8);
        if(result <= upperbound && result >= lowerbound)
            return result;
    }
}

// private functions
void BigInt::trim() {
	while(values.size() > 0 && static_cast<int>(values.back()) == 0) {
		values.pop_back();
	}
	if(values.size() == 0) {
		values.push_back(0);
	}
}
