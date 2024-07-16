#pragma once
//don't use windows.h definition of std::min
#define NOMINMAX
#include <iostream>
#include <string>
#include <stack>
#include <fstream>
#include <memory>
#include <algorithm>
#include <keyboard/DeviceKeys.h>
#include "../hotkey/Hotkey.h"
#include "../hotkey/action/Action.h"
#include "CodeBlock.h"
class Script {
private:
	std::string filename;
	std::vector<Hotkey> hotkeys;
	std::vector<CodeBlock> codeblocks;
	std::string script;
public:
	Script(const std::string& filename);
};

