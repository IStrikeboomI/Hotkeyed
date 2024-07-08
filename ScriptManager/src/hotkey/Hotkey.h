#pragma once
#include <vector>
#include <functional>
#include <keyboard/Key.h>
struct Hotkey {
	std::vector<Key> keys;
	std::function<void()> callback;

	Hotkey(std::vector<Key>& keys, std::function<void()> callback) : keys(keys), callback(callback) {}
																					
};
