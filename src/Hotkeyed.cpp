#include <iostream>
#include "windows/Interceptor.h"
#include "hotkey/HotkeyManager.h"
#include "hotkey/DeviceKeys.h"

int main() {
    DeviceManager::populate();
    std::cout << typeid(int).name() << "\n";
    //Hotkey hotkey({Key(VK_ADD)}, );
    //HotkeyManager::getInstance().addHotkey(hotkey);
    Interceptor interceptor;
}
