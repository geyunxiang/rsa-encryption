#include "BigInt.h"
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <iostream>

#define DEBUG false

// Helper functions
std::string BigInt::toHex() {
	char converted[values.size()*2+1];
	for(int i = 0; i < values.size(); i++) {
		sprintf(&converted[i*2], "%02X", static_cast<int>(values.at(values.size() - i - 1)));
	}
	return std::string(converted);
}

// get the length of this bigint
int BigInt::getLength() const {
	return values.size();
}

// get the specific byte value
byte BigInt::get(int index) const {
	return values.at(index);
}

// put value to the rear
void BigInt::put(byte value) {
	values.push_back(value);
}

// insert zeros to the lowest pos
void BigInt::insertZeros(int num) {
	for(int i = 0; i < num; i ++) {
		values.insert(values.begin(), 0);
	}
}

// insert byte value to the lowest pos
void BigInt::insert(byte value) {
	if(values.size() == 1 && values.at(0) == 0) values[0] = value;
	else values.insert(values.begin(), value);
}

// make the bigint have value
void BigInt::setValue(byte value) {
	values = std::vector<byte> (1, value);
}

// init BigInt from string or reset its value
void BigInt::setValue(std::string value) {
	unsigned int buf;
	values = std::vector<byte>();
	for(int i = value.size() - 2; i >= 0; i -= 2) {
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
}


// Four basic operations
// reference: https://stackoverflow.com/questions/269268/how-to-implement-big-int-in-c
BigInt operator+(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	byte carry = 0, op1, op2, digits_result;
	for(int count = 0; count < std::max(lop.getLength(), rop.getLength()); count ++) {
		op1 = count < lop.getLength() ? lop.get(count) : 0;
		op2 = count < rop.getLength() ? rop.get(count) : 0;
		digits_result = op1 + op2 + carry;
		if (digits_result - carry < std::max(op1, op2)) {
			carry = 1;
			if(DEBUG) std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
			
			if(DEBUG) std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
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
	if(carry == 1) result.setValue("0");
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
		if(DEBUG) std::cout << "new carry: " << static_cast<int>(carry) << std::endl;
		byte digits_result = two_digits_result; // lower 8 bit
		result.put(digits_result);
	}
	if(carry != 0) {
		result.put(carry);
	}
	return result;
}

BigInt operator*(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	result.setValue(0);
	byte nextcarry = 0, currentcarry = 0;
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
	BigInt quotion;
	BigInt zero;
	zero.setValue("0");
	while(true) {
		result ++;
		quotion.setValue(result);
		if(dividen == quotion*divider) return result;
		if(dividen - quotion*divider < divider) {
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
	BigInt dividen;
	dividen.setValue("0");
	for(int i = lop.getLength() - 1; i >= 0; i--) {
		if(DEBUG) std::cout << "i equals: " << i << std::endl;
		dividen.insert(lop.get(i));
		if(dividen < divider) {
			if(DEBUG) std::cout << "dividen < divider" << std::endl;
			result.insertZeros(1);
		} else if(dividen == divider) {
			if(DEBUG) std::cout << "dividen == divider" << std::endl;
			result.insert(1);
			dividen.setValue("0");
		} else {
			// dividen > divider but their size equals
			if(DEBUG) std::cout << "dividen before: " << dividen.toHex() << std::endl;
			byte quot = divideResult(dividen, divider);
			if(DEBUG) std::cout << "calculated quot: " << static_cast<int>(quot) << std::endl;
			BigInt quotInt;
			quotInt.setValue(quot);
			if(DEBUG) std::cout << "quotInt: " << quotInt.toHex() << std::endl;
			result.insert(quot);
			dividen = dividen - quotInt*divider;
			if(DEBUG) std::cout << "quotInt*divider: " << (quotInt*divider).toHex() << std::endl;
			if(DEBUG) std::cout << "result: " << result.toHex() << std::endl;
			if(DEBUG) std::cout << "dividen after: " << dividen.toHex() << std::endl << std::endl;
		}
	}
	result.trim();
	return result;
}

BigInt operator%(const BigInt& lop, const BigInt& rop) {
	BigInt result;
	result = lop-(lop/rop)*rop;
	return result;
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
		BigInt zero;
		zero.setValue("0");
		if(rop - lop == zero) return false;
		else return true;
	}
}

bool operator> (const BigInt& lop, const BigInt& rop) {
	return rop < lop;
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
