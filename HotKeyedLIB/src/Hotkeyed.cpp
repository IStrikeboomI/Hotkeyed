#include <iostream>
#include "windows/Interceptor.h"
#include "keyboard/DeviceKeys.h"
void keyboardCallback(const Keyboard& mouse, const KEYSTATE state, const DeviceKey& key) {
    std::wcout << mouse << " " << state << " " << key << "\n";
}
void mouseCallback(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y) {
    std::wcout << mouse << " " << state << " " << key << "\n";
}
int main() {
    Mapping mapping("mapping.mapping");
    DeviceManager::getInstance().setMapping(mapping);
    Key k(DeviceKeys::getByName("d"), UP, { DeviceIDRule(4673) });
    std::cout << k.deviceIDs.size() << "\n";
    return 0;
}
