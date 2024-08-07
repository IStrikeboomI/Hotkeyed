#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <string_view>
struct DeviceKey {
	//First name is primary name (usaully abbreviated ex. Ctrl)
	//Names after that are possible names (ex. Control)
	const std::vector<std::string_view> names;
	const unsigned char value;

	DeviceKey(const unsigned char value, const std::vector<std::string_view>& names) : names(names), value(value) {};
	friend std::wostream& operator<<(std::wostream& out, const DeviceKey& c);
	friend std::ostream& operator<<(std::ostream& out, const DeviceKey& c);
	bool operator<(const DeviceKey& rhs) const;
	bool isMouse();
	bool isKeyboard();
	bool isNone();
};