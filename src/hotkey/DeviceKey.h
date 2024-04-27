#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
struct DeviceKey {
	//First name is primary name (usaully abbreviated ex. Ctrl)
	//Names after that are possible names (ex. Control)
	const std::vector<std::string_view> names;
	const char value;

	DeviceKey(char value, std::vector<std::string_view>&& names) : names(names), value(value) {};
	friend std::ostream& operator<<(std::ostream& out, const DeviceKey& c);
};