#pragma once
#include <string>
#include <vector>
#include <string_view>
struct DeviceKey {
	//First name is primary name (usaully abbreviated ex. Ctrl)
	//Names after that are possible names (ex. Control)
	std::vector<std::string_view> names;
	char value;

	DeviceKey(char value, std::vector<std::string_view>&& names) : names(names), value(value) {};
};