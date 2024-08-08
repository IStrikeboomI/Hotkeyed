#pragma once
#include <map>
#include <set>
#include "../keyboard/Key.h"
//Class that holds keys that are actively being held down along with deviceIds
//Doesn't work with keys with up since they can only be up for an instant
class ActiveKeyStates {
private:
	std::map<DeviceKey,std::set<int>> downKeys;
public:
	void addKeyDown(const DeviceKey& key, int deviceId);
	void removeKeyDown(const DeviceKey& key, int deviceId);

	KEYSTATE isKeyBeingUsed(const Key& k);

	//test print function to see whats being pressed
	friend std::ostream& operator<<(std::ostream& out, const ActiveKeyStates& c);
};

