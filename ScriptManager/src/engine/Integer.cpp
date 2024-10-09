#include "Integer.h"

std::ostream& operator<<(std::ostream& o, const Integer& i) {
	o << i.toString();
}


Integer::Integer(long long int num) {
}

Integer::Integer(const std::string& num, int radix) {
}

std::string Integer::toString(int radix) const {
	constexpr std::array<char,64> radixChart = {'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};
	return std::string();
}
