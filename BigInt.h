#ifndef BIGINT_H
#define BIGINT_H

#include <vector>
#include <string>

typedef unsigned char byte;
// bool commandlineDebug = false;

class BigInt {
public:
    BigInt();
    BigInt(unsigned int a);
	~BigInt() {}
	friend BigInt operator+(const BigInt& lop, const BigInt& rop);// reference: https://stackoverflow.com/questions/269268/how-to-implement-big-int-in-c
	friend BigInt operator-(const BigInt& lop, const BigInt& rop);
	friend BigInt operator*(const BigInt& lop, const BigInt& rop);
	friend BigInt operator/(const BigInt& lop, const BigInt& rop);
	friend BigInt operator%(const BigInt& lop, const BigInt& rop);
    void increaseOne();
	friend bool operator< (const BigInt& lop, const BigInt& rop);
    friend bool operator<= (const BigInt& lop, const BigInt& rop);
	friend bool operator> (const BigInt& lop, const BigInt& rop);
    friend bool operator>= (const BigInt& lop, const BigInt& rop);
	friend bool operator== (const BigInt& lop, const BigInt& rop);
	friend bool operator!= (const BigInt& lop, const BigInt& rop);
	std::string toHex() const;// reference: https://stackoverflow.com/questions/5661101/how-to-convert-an-unsigned-character-array-into-a-hexadecimal-string-in-c
	int getLength() const;
	void put(unsigned int value); // put value to the rear
	void insertZeros(int num); // insert zeros to the front
	void insert(unsigned int value); // insert value to high pos
	unsigned int get(int index) const;
	void setValue(std::string value);
	void setValue(unsigned int value); // set single byte value

private:
	void trim();
	std::vector<unsigned int> values;
};

const BigInt ZERO_BIG_INT = BigInt(0);
const BigInt ONE_BIG_INT = BigInt(1);
const BigInt TWO_BIG_INT = BigInt(2);

BigInt pow(BigInt base, BigInt power);
BigInt pow(BigInt base, BigInt power, BigInt modulo); // reference: https://www.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/fast-modular-exponentiation
BigInt getRandom(BigInt lowerbound, BigInt upperbound); // both inclusive
#endif
