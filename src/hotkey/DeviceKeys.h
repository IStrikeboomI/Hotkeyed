#pragma once
#include <string>
#include <vector>
#include <functional>
#include <Winuser.h>
#include <cctype>
#include <algorithm>
#include <string_view>

#include "DeviceKey.h"

//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
namespace DeviceKeys {
	static std::vector<std::reference_wrapper<DeviceKey>> keys;
	//Helper function to add and create DeviceKey at same time
	DeviceKey& add(DeviceKey&& key) {
		keys.push_back(key);
		return key;
	}

	static DeviceKey LBUTTON = add(DeviceKey(VK_LBUTTON,{"LButton","Left Key", "Left Click"}));
	static DeviceKey RBUTTON = add(DeviceKey(VK_RBUTTON, { "RButton","Right Key", "Right Click" }));

	//Gets device key by case insensitive search 
	DeviceKey& getByName(const std::string& name) {
		for (std::reference_wrapper<DeviceKey> key : keys) {
			for (std::string_view n : key.get().names) {
				if (std::ranges::equal(std::string_view(name), n, [](auto a, auto b) {return std::tolower(a) == std::tolower(b); })) {
					return key;
				}
			}
		}
	}

}