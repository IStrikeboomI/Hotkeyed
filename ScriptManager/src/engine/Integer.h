#pragma once
#include <array>
#include <vector>
#include <string>
//Represents a general integer with any bound, its dynamic
class Integer {
private:
	char signum = 0;
	//big endian bytes of integer
	std::vector<unsigned char> bytes;
public:
	Integer(long long int num);
	Integer(const std::string& num, int radix = 10);

	std::string toString(int radix = 10) const ;
	friend std::ostream& operator<<(std::ostream&, const Integer&);
	//friend std::istream& operator>>(istream&, BigInt&);
};

