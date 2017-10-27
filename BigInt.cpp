#include "BigInt.h"
#include <algorithm>
#include <sstream>
#include <cstdio>
#include <iostream>

// reference: https://stackoverflow.com/questions/5661101/how-to-convert-an-unsigned-character-array-into-a-hexadecimal-string-in-c
std::string BigInt::toHex() {
	char converted[values.size()*2+1];
	for(int i = 0; i < values.size(); i++) {
		sprintf(&converted[i*2], "%02X", static_cast<int>(values.at(values.size() - i - 1)));
	}
	return std::string(converted);
}

int BigInt::getLength() const {
	return values.size();
}

byte BigInt::get(int index) const {
	return values.at(index);
}

void BigInt::put(byte value) {
	values.push_back(value);
}

void BigInt::insert(int num) {
	for(int i = 0; i < num; i ++) {
		values.insert(values.begin(), 0);
	}
}

// init BigInt from string
void BigInt::setValue(std::string value) {
	unsigned int buf;
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
			// std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
			
			// std::cout << "digits_result: " << static_cast<int>(digits_result) << std::endl;
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
		result.put(0);
		return result;
	}
	int count;
	for(count = 0; count < rop.getLength(); count ++) {
		op1 = lop.get(count);
		op2 = rop.get(count);
		digits_result = op1 - op2 - carry;
		if(digits_result - carry > op1) {
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
	result.put(0);
	byte nextcarry = 0, currentcarry = 0;
	BigInt multiresults[rop.getLength()];
	for(int count = 0; count < rop.getLength(); count ++) {
		BigInt singlerop;
		singlerop.put(rop.get(count));
		multiresults[count] = multiplyOneDigit(lop, singlerop);
		multiresults[count].insert(count);
		result = result + multiresults[count];
	}
	return result;
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
