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
    Interceptor interceptor;
    interceptor.keyboardGlobalInterceptors.push_back(keyboardCallback);
    interceptor.mouseGlobalInterceptors.push_back(mouseCallback);
    interceptor.begin();
    return 0;
}
