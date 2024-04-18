#pragma once
#include <string>
#include <vector>
#include <functional>
#include <Winuser.h>
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

}