#include "BigInt.hpp"
#include <algorithm>
#include <sstream>
#include <chrono>
#include <random>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#define DEBUG false

const int RESERVED_LENGTH = 500;

// constructor
BigInt::BigInt() {
    values.reserve(RESERVED_LENGTH);
    negative = false;
}

BigInt::BigInt(unsigned int a) {
    values.reserve(RESERVED_LENGTH);
    values.push_back(a);
    negative = false;
}

// Helper functions
std::string BigInt::toHex() const {
	char converted[values.size()*8+2];
    converted[0] = negative ? '-' : '+';
	for(int i = 0; i < values.size(); i++) {
		sprintf(&converted[i*8+1], "%08X", values.at(values.size() - i - 1));
	}
    std::string result(converted);
    // std::replace(result.begin(), result.end(), '0', '');
	return result;
}

// get the length of this bigint
int BigInt::getLength() const {
	return static_cast<int>(values.size());
}

// get the specific position value
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

// insert value to the lowest pos
void BigInt::insert(unsigned int value) {
	if(values.size() == 1 && values.at(0) == 0) values[0] = value;
	else values.insert(values.begin(), value);
}

// set the value of this bigint
void BigInt::setValue(unsigned int value) {
	values = std::vector<unsigned int> (1, value);
    values.reserve(RESERVED_LENGTH);
    negative = false;
}

// init BigInt from string or reset its value
void BigInt::setValue(std::string value) {
    value.erase(std::remove(value.begin(), value.end(), '+'), value.end());
	unsigned int buf;
	values = std::vector<unsigned int>();
    values.reserve(RESERVED_LENGTH);
	for(int i = static_cast<int>(value.size()) - 8; i >= 0; i -= 8) {
		std::stringstream ss;
		ss << std::hex << value.substr(i, 8); // 8 hex per int
		ss >> buf;
		values.push_back(buf);
		ss.str("");
	}
	if(value.size() % 8 != 0) {
		std::stringstream ss;
		ss << std::hex << value.substr(0, value.size() % 8);
		ss >> buf;
		values.push_back(buf);
	}
	this->trim();
    negative = false;
}

// Four basic operations
void BigInt::reverseSign() {
    this->negative = !this->negative;
}

// The sign of inputs to this function must be consistent.
// I.e., either all positive or all negative
BigInt operator+(const BigInt& lop, const BigInt& rop) {
    if(lop.isNegative() && !rop.isNegative()) {
        BigInt newlop = lop;
        newlop.reverseSign();
        return rop-newlop;
    }
    if(rop.isNegative() && !lop.isNegative()) {
        BigInt newrop = rop;
        newrop.reverseSign();
        return lop-newrop;
    }
    BigInt result;
	unsigned int carry = 0, op1, op2, digits_result;
	for(int count = 0; count < std::max(lop.getLength(), rop.getLength()); count ++) {
		op1 = count < lop.getLength() ? lop.get(count) : 0;
		op2 = count < rop.getLength() ? rop.get(count) : 0;
		digits_result = op1 + op2 + carry;
		if (digits_result - carry < std::max(op1, op2)) {
			carry = 1;
		} else {
			carry = 0;
		}
		result.put(digits_result);
	}
	if(carry != 0) 
		result.put(carry);
    if(lop.isNegative() && rop.isNegative()) result.reverseSign();
    result.trim();
	return result;
}

// lop should not be negative (should be positive or zero)
//      -- if lop < 0 and rop < 0, return rop.reverseSign() - lop.reverseSign() (-3-(-5)) == (5 - 3)
//      -- if lop < 0 and rop >= 0, return lop + rop.reverseSign() (-3-5) == ((-3) + (-5))
//      -- if lop >= 0 and rop < 0, return lop + rop.reverseSign() (5-(-3)) == (5 + 3)
//      -- if lop >= 0 and rop >= 0, proceed.
//          -- if lop >= rop, proceed.
//          -- if lop < rop, return -(rop-lop)
BigInt operator-(const BigInt& lop, const BigInt& rop) {
    if(lop.isNegative()) {
        BigInt newlop = lop, newrop = rop;
        if(rop.isNegative()) {
            newrop.reverseSign();
            newlop.reverseSign();
            return newrop - newlop;
        }
        newrop.reverseSign();
        return newlop + newrop;
    }
    if(rop.isNegative()) {
        BigInt newrop = rop;
        newrop.reverseSign();
        return lop + newrop;
    }
    // lop >= 0, rop >= 0
    BigInt result;
    if(lop < rop) {
        result = rop - lop;
        result.reverseSign();
        return result;
    }
	unsigned int carry = 0, op1, op2, digits_result;
	int count;
	for(count = 0; count < rop.getLength(); count ++) {
        op1 = count < lop.getLength() ? lop.get(count) : 0;
		op2 = rop.get(count);
		digits_result = op1 - op2 - carry;
		if(digits_result + carry > op1) {
			carry = 1;
        } else if(digits_result + carry == 0 && carry == 1) {
            // if op1 - op2 == 0, and carry = 1, then still set carry = 1
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
    if(carry == 1) {
        std::cout << "This code should never be executed as well" << std::endl;
        std::cout << "lop: " << lop.toHex() << std::endl;
        std::cout << "rop: " << rop.toHex() << std::endl;
        result.reverseSign();
    }
	result.trim();
	return result;
}

// rop only contains one digit
// Deprecated
BigInt multiplyOneDigit(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	unsigned int op2 = rop.get(0);
	unsigned int carry = 0;
	for(int count = 0; count < lop.getLength(); count ++) {
		unsigned int op1 = lop.get(count);
		uint64_t two_digits_result = static_cast<uint64_t>(op1)*static_cast<uint64_t>(op2);
		two_digits_result += carry;
		carry = two_digits_result >> 32; // carry
		unsigned int digits_result = static_cast<unsigned int>(two_digits_result); // lower 32 bit
		result.put(digits_result);
	}
	if(carry != 0) {
		result.put(carry);
	}
	return result;
}

BigInt multiplyOneDigit(const BigInt& lop, unsigned int op2) {
    BigInt result;
    unsigned int carry = 0;
    for(int count = 0; count < lop.getLength(); count ++) {
        unsigned int op1 = lop.get(count);
        uint64_t two_digits_result = static_cast<uint64_t>(op1)*static_cast<uint64_t>(op2);
        two_digits_result += carry;
        carry = two_digits_result >> 32; // carry
        unsigned int digits_result = static_cast<unsigned int>(two_digits_result); // lower 32 bit
        result.put(digits_result);
    }
    if(carry != 0) {
        result.put(carry);
    }
    return result;
}

BigInt operator*(const BigInt& lop, const BigInt& rop) {
	BigInt result(0);
    BigInt posresult;
	for(int count = 0; count < rop.getLength(); count ++) {
		posresult = multiplyOneDigit(lop, rop.get(count));
		posresult.insertZeros(count);
		// posresult.trim();
		result = result + posresult;
	}
    if(lop.isNegative() && !rop.isNegative()) result.reverseSign();
    if(!lop.isNegative() && rop.isNegative()) result.reverseSign();
    result.trim();
	return result;
}

unsigned int divideResult(const BigInt& dividen, const BigInt& divider) {
	// this should return a value less than uint.max
    // currently this function need to be speed up
	unsigned int result = 0, min = 0, max = 4294967295;
    BigInt multResult(0);
    while(true) {
        if(max - min < 10) {
            // search manually
            for(result = min; result <= max; result ++) {
                multResult = multiplyOneDigit(divider, result);
                //std::cout << dividen.toHex() << "  dividen\n";
                //std::cout << multResult.toHex() << "  multresult\n";
                //std::cout << (dividen-multResult).toHex() << "  dividen-multresult\n";
                //std::cout << divider.toHex() << "  divider\n";
                if(dividen == multResult) return result;
                if(dividen - multResult < divider) {
                    return result;
                }
            }
            std::cout << "this code should never be executed." << std::endl;
        }
        result = max/2 + min/2;
        multResult = multiplyOneDigit(divider, result);
        if(dividen == multResult) return result;
        if(dividen > multResult) {
            // result too small
            min = result;
            continue;
        }
        if(dividen < multResult) {
            // result too big
            max = result;
            continue;
        }
    }
    /*
	while(true) {
		result ++;
        multResult = multResult + divider;
		//quotion.setValue(result);
		
		if(result == 4294967295) return result;
	}*/
}

BigInt operator/(const BigInt& lop, const BigInt& divider) {
	BigInt result;
	if(lop < divider) {
		result.setValue(0);
		return result;
	}
	BigInt dividen(0);
	for(int i = lop.getLength() - 1; i >= 0; i--) {
		dividen.insert(lop.get(i));
		if(dividen < divider) {
            //std::cout << dividen.toHex() << "  dividen less than" << std::endl;
            //std::cout << divider.toHex() << std::endl;
			result.insertZeros(1);
		} else if(dividen == divider) {
            //std::cout << "divider == dividen" << std::endl;
			result.insert(1);
			dividen.setValue(0);
		} else {
			// dividen > divider but their size equals
			unsigned int quot = divideResult(dividen, divider);
            //std::cout << "quot equals: " << quot << std::endl;
			result.insert(quot);
            //std::cout << "origin dividen equals: " << dividen.toHex() << std::endl;
            //std::cout << "mult result: " << multiplyOneDigit(divider, quot).toHex() << std::endl;
			dividen = dividen - multiplyOneDigit(divider, quot);
            //std::cout << "dividen equals: " << dividen.toHex() << std::endl;
		}
	}
	result.trim();
	return result;
}

BigInt operator%(const BigInt& lop, const BigInt& divider) {
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
            unsigned int quot = divideResult(dividen, divider);
            dividen = dividen - multiplyOneDigit(divider, quot);
        }
    }
    dividen.trim();
    return dividen;
}

void BigInt::increaseOne() {
    unsigned int carry = 0, oldValue = values[0];
    values[0] ++;
    for(int count = 0; count < values.size(); count ++) {
        if(count != 0) {
            oldValue = values[count];
        }
        values[count] += carry;
        if (values[count] < oldValue) {
            carry = 1;
        } else {
            carry = 0;
            break;
        }
    }
    if(carry != 0) 
        values.push_back(carry);
}


// Comparisons
bool operator== (const BigInt& lop, const BigInt& rop) {
	if(lop.getLength() != rop.getLength()) return false;
    if(lop.isNegative() && !rop.isNegative()) return false;
    if(!lop.isNegative() && rop.isNegative()) return false;
	for(int i = 0; i < lop.getLength(); i++) {
		if(lop.get(i) != rop.get(i)) return false;
	}
	return true;
}

bool operator!= (const BigInt& lop, const BigInt& rop) {return !(lop==rop);}

// implemented independent of minus operator
bool operator< (const BigInt& lop, const BigInt& rop) {
    if(lop.isNegative() && !rop.isNegative()) return true;
    if(!lop.isNegative() && rop.isNegative()) return false;
    if(lop.isNegative() && rop.isNegative()) {
        // -3 < -5 ? <==> 5 < 3 ?
        BigInt newlop = lop, newrop = rop;
        newlop.reverseSign();
        newrop.reverseSign();
        return newrop < newlop;
    }
    // lop >= 0, rop >= 0
    if(lop.getLength() < rop.getLength()) {
		return true;
	} else if(lop.getLength() > rop.getLength()) {
		return false;
    } else if(rop == lop){
        return false;
    } else {
        // length equals and the two number does not equal
        unsigned int carry = 0, op1, op2, digits_result;
        int count;
        for(count = 0; count < rop.getLength(); count ++) {
            op1 = lop.get(count);
            op2 = rop.get(count);
            digits_result = op1 - op2 - carry;
            if(digits_result + carry > op1) {
                carry = 1;
            } else if(digits_result + carry == 0 && carry == 1) {
                // if op1 - op2 == 0, and carry = 1, then still set carry = 1
                carry = 1;
            } else {
                carry = 0;
            }
        }
        if(carry == 1) return true;
        return false;
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

bool BigInt::isNegative() const {
    return this->negative;
}

// Other functions
BigInt pow(BigInt base, BigInt power) {
    BigInt result(1);
    BigInt counter;
    for(counter.setValue(0); counter < power; counter.increaseOne()){
        result = result * base;
    }
    return result;
}

BigInt pow(BigInt base, BigInt power, BigInt modulo) {
    int listLength = power.getLength()*32;
    BigInt* powModuloResult = new BigInt[listLength]; // base^(2^i) % modulo = powModuloResult[i]
    //BigInt powModuloResult[256];
    powModuloResult[0] = base % modulo; // base^(2^0) = base^1 = base % modulo
    for(int i = 1; i < listLength; i++) {
        //BigInt multResult = powModuloResult[i-1] * powModuloResult[i-1];
        //powModuloResult[i] = (multResult) % modulo;
        powModuloResult[i] = (powModuloResult[i-1] * powModuloResult[i-1]) % modulo;
        //std::cout << "powmodule " << i << " : " << powModuloResult[i].toHex() << std::endl;
    }
    std::cout << "powModule list built" << std::endl;
    BigInt result(1);
    BigInt powerLeft = power;
    BigInt tmp;
    for(int i = listLength-1; i >= 0; i--) {
        tmp = pow(TWO_BIG_INT, BigInt(i));
        while(true) {
            if(powerLeft < tmp) break;
            result = result * powModuloResult[i] % modulo;
            powerLeft = powerLeft - tmp;
            //std::cout << "result: " << result.toHex() << std::endl;
        }
        //std::cout << "powerLeft: " << powerLeft.toHex() << std::endl;
    }
    //std::cout << "powerLeft: " << powerLeft.toHex() << std::endl;
    delete [] powModuloResult;
    return result;
}

BigInt getRandomWithBitLength(int bitLength) {
    int vectorLength = bitLength / 8;
    BigInt result;
    unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 generator (seed);
    for(int i = 0; i < vectorLength; i++)
        result.put(static_cast<unsigned int>(generator()%4294967295));
    return result;
}

BigInt getRandom(BigInt lowerbound, BigInt upperbound) {
    BigInt result;
    int lowerLength = lowerbound.getLength(), upperLength = upperbound.getLength();
    int lengthGap = upperLength - lowerLength;
    int randGap = 0;
    unsigned seed = static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count());
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
	while(values.size() > 0 && values.back() == 0) {
		values.pop_back();
	}
	if(values.size() == 0) {
		values.push_back(0);
	}
}
