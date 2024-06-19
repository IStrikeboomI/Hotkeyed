 #include <iostream>
#include "windows/Interceptor.h"
#include "hotkey/HotkeyManager.h"
#include "keyboard/DeviceKeys.h"
void keyboardCallback(const Keyboard& mouse, const KEYSTATE state, const DeviceKey& key) {
    std::wcout << mouse << " " << state << " " << key << "\n";
}
void mouseCallback(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y) {
    std::wcout << mouse << " " << state << " " << key << "\n";
}
int main() {
    DeviceManager::populate();
    DeviceManager::createOrApplyMapping("mapping.mapping");
    for (std::shared_ptr<Device> d : DeviceManager::devices) {
        std::cout << d->id << "\n";
    }
    return 0;
}
