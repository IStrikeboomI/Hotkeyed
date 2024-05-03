 #include <iostream>
#include "windows/Interceptor.h"
#include "hotkey/HotkeyManager.h"
#include "hotkey/DeviceKeys.h"
#include <filesystem>
int main() {
    DeviceManager::populate();
    DeviceManager::createOrApplyMapping("mapping.mapping");
    Interceptor interceptor;
    interceptor.keyboardGlobalInterceptors.push_back([](const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key) {std::cout << key << "\n"; });
    interceptor.begin();
   
}
