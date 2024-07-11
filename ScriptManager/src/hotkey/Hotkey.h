#pragma once
#include <vector>
#include <memory>
#include <keyboard/Key.h>
#include "action/Action.h"
class Hotkey {
private:
	std::vector<Key> keys;
	std::vector<std::unique_ptr<Action>> actions;
public:
	Hotkey(std::vector<Key>& keys);
	
	void addAction(const Action& action);
};

