 #include <iostream>
#include "windows/Interceptor.h"
#include "hotkey/HotkeyManager.h"
#include "hotkey/DeviceKeys.h"
#include <filesystem>
int main() {
    DeviceManager::populate();
    DeviceManager::createOrApplyMapping("mapping.mapping");
    //Hotkey hotkey({Key(VK_ADD)}, );
    //HotkeyManager::getInstance().addHotkey(hotkey);
    //Interceptor interceptor;
    //interceptor.keyboardGlobalInterceptors.push_back([](const Keyboard& keyboard, const KEYSTATE state, const DeviceKey& key) {std::wcout << keyboard << " " << state << "\n"; });
    //interceptor.begin();
   
}
