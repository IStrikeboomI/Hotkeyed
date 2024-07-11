#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <memory>
#include "../hotkey/Hotkey.h"
#include "../hotkey/action/Action.h"
class Script {
private:
	std::string filename;
	std::vector<Hotkey> hotkeys;
public:
	Script(const std::string& filename);
};

