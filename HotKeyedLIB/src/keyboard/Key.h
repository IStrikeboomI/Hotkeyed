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
	//If -1, then global to all keyboards
	std::vector<DeviceIDRule> deviceIDs;
	Key(const DeviceKey& key, const KEYSTATE state = DOWN, const std::vector<DeviceIDRule>& deviceIds = std::vector<DeviceIDRule>(1,DeviceIDRule())) : key(key), state(state), deviceIDs(deviceIDs) {};
};