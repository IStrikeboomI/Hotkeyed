#include "HotkeyManager.h"

HotkeyManager::HotkeyManager() {

}
HotkeyManager& HotkeyManager::getInstance() {
    static HotkeyManager instance;
    return instance;
}

void HotkeyManager::addHotkey(Hotkey& hotkey) {
}

void HotkeyManager::dispatch(Keyboard& keyboard, Key& key) {
}

