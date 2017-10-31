#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <string>

typedef unsigned char byte;

class BigInt {
public:
	BigInt() {}
	~BigInt() {}
	friend BigInt operator+(const BigInt& lop, const BigInt& rop);
	friend BigInt operator-(const BigInt& lop, const BigInt& rop);
	friend BigInt operator*(const BigInt& lop, const BigInt& rop);
	friend BigInt operator/(const BigInt& lop, const BigInt& rop);
	friend BigInt operator%(const BigInt& lop, const BigInt& rop);
	friend bool operator< (const BigInt& lop, const BigInt& rop);
	friend bool operator> (const BigInt& lop, const BigInt& rop);
	std::string toHex();
	int getLength() const;
	void put(byte value); // put value to the rear
	void insert(int num); // insert zero to the front
	void insert(byte value); // insert value to high pos
	byte get(int index) const;
	void setValue(std::string value);

private:
	void trim();
	std::vector<byte> values;
};
// BigInt trimmed();
#endif