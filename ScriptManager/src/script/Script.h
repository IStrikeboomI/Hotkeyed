#pragma once
#include <string>
#include <map>
#include "../hotkey/Hotkey.h"
#include "../hotkey/action/Action.h"
class Script {
private:
	std::string filename;
	std::map<Hotkey, Action> hotkeys;
public:
	Script(std::string&& filename);
};

