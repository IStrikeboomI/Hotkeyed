#pragma once
#include <string>
#include <vector>
struct DeviceKey {
	//First name is primary name (usaully abbreviated ex. Ctrl)
	//Names after that are possible names (ex. Control)
	std::vector<std::string> names;
	char value;

	DeviceKey(char value, std::vector<std::string>&& names) : names(names), value(value) {};
};