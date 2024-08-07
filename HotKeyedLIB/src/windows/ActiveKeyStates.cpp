#include "ActiveKeyStates.h"

KEYSTATE ActiveKeyStates::isKeyBeingUsed(const Key& k) {
    DeviceKey dk = k.key;
    if (downKeys.contains(dk)) {
        for (int id : downKeys[dk]) {
            if (k.isDeviceIdValid(id)) {
                return DOWN;
            }
        }
    }
    if (upKeys.contains(dk)) {
        for (int id : upKeys[dk]) {
            if (k.isDeviceIdValid(id)) {
                return UP;
            }
        }
    }
    return NONE;
}

void ActiveKeyStates::addKeyDown(const DeviceKey& key, int deviceId) {
    if (downKeys.contains(key)) {
        downKeys[key].insert(deviceId);
    } else {
        downKeys[key] = { deviceId };
    }
}

void ActiveKeyStates::removeKeyDown(const DeviceKey& key, int deviceId) {
    if (downKeys.contains(key)) {
        downKeys[key].erase(downKeys[key].find(deviceId));
    }
}

void ActiveKeyStates::addKeyUp(const DeviceKey& key, int deviceId) {
    if (upKeys.contains(key)) {
        upKeys[key].insert(deviceId);
    } else {
        upKeys[key] = { deviceId };
    }
}

void ActiveKeyStates::removeKeyUp(const DeviceKey& key, int deviceId) {
    if (upKeys.contains(key)) {
        upKeys[key].erase(upKeys[key].find(deviceId));
    }
}
