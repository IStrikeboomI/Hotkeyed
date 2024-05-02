#pragma once
#include <string>
#include <set>
#include <functional>
#include <Windows.h>
#include <Winuser.h>
#include <cctype>
#include <algorithm>
#include <string_view>
#include <memory>

#include "DeviceKey.h"

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace DeviceKeys {
	extern std::set<DeviceKey> keys;

	//Gets device key by case insensitive search 
	static const DeviceKey getByName(const std::string& name) {
		for (DeviceKey key : keys) {
			for (std::string_view n : key.names) {
				if (std::ranges::equal(std::string_view(name), n, [](auto a, auto b) {return std::tolower(a) == std::tolower(b); })) {
					return key;
				}
			}
		}
		return *keys.begin();
	}
	static const DeviceKey getByVKey(const int vKey) {
		for (DeviceKey key : keys) {
			if (vKey == key.value) {
				return key;
			}
		}
		return *keys.begin();
	}
}