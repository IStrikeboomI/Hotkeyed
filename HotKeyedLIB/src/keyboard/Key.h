#pragma once
#include "DeviceKey.h"
#include "DeviceIDRule.h"
enum KEYSTATE {
	DOWN,
	UP,
	CLICK,
	NONE
};
struct Key {
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	const DeviceKey key;
	const KEYSTATE state = DOWN;
	//If unsigned integer limit (2^32 - 1) then global to all keyboards
	const std::vector<DeviceIDRule> deviceIDs;
	Key(const DeviceKey& key, const KEYSTATE state = DOWN,  const std::vector<DeviceIDRule>& deviceIDs = {DeviceIDRule()}) : key(key), state(state), deviceIDs(deviceIDs) {};

	//If any of the device id rules is global to all devices, then returns true
	bool isGlobalToAllDevices() {
		for (DeviceIDRule rule : deviceIDs) {
			if (rule.start == (std::numeric_limits<unsigned int>::max)() && rule.end == (std::numeric_limits<unsigned int>::max)()) {
				return true;
			}
		}
		return false;
	}
};