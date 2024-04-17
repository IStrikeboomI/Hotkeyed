#pragma once
#include <vector>
#include <functional>
#include "Key.h"
#include "../device/Keyboard.h"
class Hotkey {
public:
	std::vector<Key> keys;
	std::function<void> callback;

	Hotkey(std::vector<Key> keys, std::function<void> callback);
	bool executeIfValid(Keyboard keyboard, Key key);
};

