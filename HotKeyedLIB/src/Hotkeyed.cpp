#include <iostream>
#include "windows/Interceptor.h"
#include "keyboard/DeviceKeys.h"
Interceptor interceptor;
void keyboardCallback(const Keyboard& mouse, const KEYSTATE state, const DeviceKey& key) {
    
}
void mouseCallback(const Mouse& mouse, const KEYSTATE state, const DeviceKey& key, int x, int y) {
    //std::wcout << mouse << " " << state << " " << key << "\n";
    if (state == DOWN) {
        std::cout << interceptor.activeKeyStates << "\n";
    }
}
int main() {
    Mapping mapping("mapping.mapping");
    DeviceManager::getInstance().setMapping(mapping);
    interceptor.keyboardGlobalInterceptors.push_back(keyboardCallback);
    interceptor.mouseGlobalInterceptors.push_back(mouseCallback);
    interceptor.begin();
    return 0;
}
