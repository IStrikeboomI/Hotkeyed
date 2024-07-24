#pragma once
#include <vector>
#include <memory>
#include <keyboard/Key.h>
#include "action/Action.h"
class Hotkey {
private:
	
	//std::vector<std::shared_ptr<Action>> actions;
public:
	std::vector<Key> keys;
	Hotkey(std::vector<Key>& keys);
	
	void addAction(const Action& action);
};

