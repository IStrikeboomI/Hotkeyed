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
#include "../Util.h"

#include "DeviceKey.h"

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace DeviceKeys {
	extern std::set<DeviceKey> keys;

	//Gets device key by case insensitive search 
	static const DeviceKey getByName(const std::string& name) {
		for (DeviceKey key : keys) {
			for (std::string_view n : key.names) {
				if (Util::caseInsensitiveEquals(std::string{n},name)) {
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