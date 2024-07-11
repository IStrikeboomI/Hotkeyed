#include "Hotkey.h"

Hotkey::Hotkey(std::vector<Key>& keys) : keys(keys) {
	
}

void Hotkey::addAction(const Action& action) {
	actions.push_back(std::make_unique<Action>(action));
}
