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
        if (downKeys[key].size() == 0) {
            downKeys.erase(downKeys.find(key));
        }
    }
}

std::ostream& operator<<(std::ostream& out, const ActiveKeyStates& c) {
    out << "{";
    for (auto const& [key, value] : c.downKeys) {
        out << key.names[0];
        out << ": {";
        for (int id : value) {
            out << id;
            out << ", ";
        }
        out << "}, ";
    }
    out << "}";
    return out;
}
