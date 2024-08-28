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

//Characters/Strings that cannot be the start of functions and variables

class Script {
private:
	std::string filename;
	std::vector<TextBlock> codeblocks;
	std::vector<TextBlock> hotkeyBlocks;
	std::vector<TextBlock> squareBracketBlocks;
	std::vector<TextBlock> functionBlocks;
	std::vector<TextBlock> globalLines;
	std::string script;
	bool isIndexInGlobal(int index);
public:

	std::vector<Hotkey> hotkeys;
	Script(const std::string& filename);
};

