#pragma once
#include <vector>
#include <memory>
#include <keyboard/Key.h>
#include "action/Action.h"
#include "ScriptFunction.h"
//Hotkey is basically function with no parameters or name
class Hotkey : public ScriptFunction{
public:
	std::vector<Key> keys;
	Hotkey(std::vector<Key>& keys);
	
};

