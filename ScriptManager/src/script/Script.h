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
#include "TextBlock.h"
#include <Util.h>
class Script {
private:
	std::string filename;
	std::vector<TextBlock> codeblocks;
	std::vector<TextBlock> hotkeyBlocks;
	std::vector<TextBlock> functionBlocks;
	std::vector<TextBlock> globalLines;
	std::string script;
public:
	std::vector<Hotkey> hotkeys;
	Script(const std::string& filename);
};

