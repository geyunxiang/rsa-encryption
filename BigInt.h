#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <string>

typedef unsigned char byte;
// bool commandlineDebug = false;

class BigInt {
public:
	BigInt() {}
    BigInt(int a) {values.push_back(a);}
	~BigInt() {}
	friend BigInt operator+(const BigInt& lop, const BigInt& rop);
	friend BigInt operator-(const BigInt& lop, const BigInt& rop);
	friend BigInt operator*(const BigInt& lop, const BigInt& rop);
	friend BigInt operator/(const BigInt& lop, const BigInt& rop);
	friend BigInt operator%(const BigInt& lop, const BigInt& rop);
    friend BigInt operator++(const BigInt& lop);
	friend bool operator< (const BigInt& lop, const BigInt& rop);
    friend bool operator<= (const BigInt& lop, const BigInt& rop);
	friend bool operator> (const BigInt& lop, const BigInt& rop);
    friend bool operator>= (const BigInt& lop, const BigInt& rop);
	friend bool operator== (const BigInt& lop, const BigInt& rop);
	friend bool operator!= (const BigInt& lop, const BigInt& rop);
	std::string toHex();// reference: https://stackoverflow.com/questions/5661101/how-to-convert-an-unsigned-character-array-into-a-hexadecimal-string-in-c
	int getLength() const;
	void put(byte value); // put value to the rear
	void insertZeros(int num); // insert zero to the front
	void insert(byte value); // insert value to high pos
	byte get(int index) const;
	void setValue(std::string value);
	void setValue(byte value); // set single byte value

private:
	void trim();
	std::vector<byte> values;
};

const BigInt ZERO_BIG_INT = BigInt(0);
const BigInt ONE_BIG_INT = BigInt(1);

BigInt pow(BigInt base, BigInt power);
BigInt getRandom(BigInt lowerbound, BigInt upperbound); // both inclusive

// BigInt trimmed();
#endif
