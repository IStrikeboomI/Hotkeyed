#include "DeviceKey.h"
enum KEYSTATE {
	DOWN,
	UP,
	CLICK
};
struct Key {
	//https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	DeviceKey key;
	KEYSTATE state = DOWN;
	//If -1, then global to all keyboards
	int deviceId;
	Key(DeviceKey& key, KEYSTATE state = DOWN, int deviceId = -1) : key(key), state(state), deviceId(deviceId) {};
};