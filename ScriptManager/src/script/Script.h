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
#include "../hotkey/action/CallableAction.h"
#include "../hotkey/action/ActionManager.h"
#include "TextBlock.h"
#include <Util.h>
#include <utility>

//Characters/Strings that cannot be the start of functions and variables
class Script {
private:
	std::vector<TextBlock> codeblocks;
	std::vector<TextBlock> hotkeyBlocks;
	std::vector<TextBlock> squareBracketBlocks;
	std::vector<TextBlock> functionBlocks;
	std::vector<TextBlock> globalLines;
	std::vector<TextBlock> quotationBlocks;
	std::string script;

	bool isIndexInGlobal(int index) const;
	bool isIndexInQuotations(int index) const;
	bool doesTextBlockContain(const TextBlock& tb, const std::string& string) const;
	std::pair<int,int> getLineAndCharacterFromIndex(int index) const;
	int getIndexOfText(const std::string& string,int offset = 0) const;
	std::string getTextFromTextBlock(const TextBlock& tb) const ;
	//checks if a piece of text is a valid callable action (has an action name and parentheses pair)
	bool isCallableAction(const std::string& text) const;
	void addCallableAction(const std::string& text);
public:
	std::string filename;
	std::vector<Hotkey> hotkeys;
	std::vector<CallableAction> globalActions;
	Script(const std::string& filename);
};

