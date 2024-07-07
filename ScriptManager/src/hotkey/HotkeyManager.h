#pragma once
#include "Hotkey.h"
#include <device/Keyboard.h>
#include <vector>
class HotkeyManager {
private:
	std::vector<Hotkey> hotkeys;
	//private constructor because singleton
	HotkeyManager();
public:
	void addHotkey(Hotkey& hotkey);
	void dispatch(Keyboard& keyboard, Key& key);

	static HotkeyManager& getInstance();

	//don't implement these two or else we might get multiple copies
	HotkeyManager(const HotkeyManager&) = delete;
	void operator=(const HotkeyManager&) = delete;
};

