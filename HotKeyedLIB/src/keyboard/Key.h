#pragma once
#include "DeviceKey.h"
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
	const int deviceId;
	Key(const DeviceKey& key, const KEYSTATE state = DOWN, const int deviceId = -1) : key(key), state(state), deviceId(deviceId) {};
};