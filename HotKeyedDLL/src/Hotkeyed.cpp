 #include <iostream>
#include "windows/Interceptor.h"
#include "hotkey/HotkeyManager.h"
#include "keyboard/DeviceKeys.h"
#include <filesystem>
int main() {
    DeviceManager::populate();
    DeviceManager::createOrApplyMapping("mapping.mapping");
    Interceptor interceptor;
    interceptor.begin();
    return 0;
}
