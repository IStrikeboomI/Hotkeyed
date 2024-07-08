#pragma once
#include <string>
#include <map>
#include <fstream>
#include <memory>
#include "../hotkey/Hotkey.h"
#include "../hotkey/action/Action.h"
class Script {
private:
	std::string filename;
	std::map<Hotkey, std::unique_ptr<Action>> hotkeys;
public:
	Script(std::string&& filename);
};

