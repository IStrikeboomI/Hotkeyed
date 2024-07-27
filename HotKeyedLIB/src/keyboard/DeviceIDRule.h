#pragma once
#define NOMINMAX
#include <limits>
struct DeviceIDRule {
	//If true then does numbers that are NOT in range
	//Signified by an exclamation point before range/number
	//ex. !9, !1-10
	const bool exclude = false;
	//range of valid numbers
	//if only 1 device id then start and end are same
	const unsigned int start = (std::numeric_limits<unsigned int>::max)(), end = (std::numeric_limits<unsigned int>::max)();

	DeviceIDRule(const unsigned int start, const unsigned int end, const bool exclude = false) : exclude(exclude), start(start), end(end) {};
	DeviceIDRule(const unsigned int num = (std::numeric_limits<unsigned int>::max)(), const bool exclude = false) : exclude(exclude), start(num), end(num) {};
};