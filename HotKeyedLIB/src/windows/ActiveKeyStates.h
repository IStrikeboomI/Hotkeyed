#pragma once
#include <map>
#include <set>
#include "../keyboard/Key.h"
class ActiveKeyStates {
private:
	std::map<DeviceKey,std::set<int>> downKeys;
	std::map<DeviceKey, std::set<int>> upKeys;
public:
	void addKeyDown(const DeviceKey& key, int deviceId);
	void removeKeyDown(const DeviceKey& key, int deviceId);
	void addKeyUp(const DeviceKey& key, int deviceId);
	void removeKeyUp(const DeviceKey& key, int deviceId);

	KEYSTATE isKeyBeingUsed(const Key& k);
};

