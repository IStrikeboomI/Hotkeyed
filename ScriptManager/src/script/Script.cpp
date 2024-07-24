#include "Script.h"

Script::Script(const std::string& filename) : filename(filename) {
	std::ifstream file(filename);
	std::string line;
	while (std::getline(file, line)) {
		//ignore lines that start with "//" because that signifies a comment
		if (!line.starts_with("//")) {
			script += line + "\n";
		}
	}
	//Add all isolatedd bracket pairs
	std::stack<int> bracketAtStack;
	for (int i = 0; i < script.size();i++) {
		if (script[i] == '{') {
			bracketAtStack.push(i);
		}
		if (script[i] == '}') {
			if (!bracketAtStack.empty()) {
				//filter out code blocks that are isolated (not inside another code block)
				//this filters out anything in quotations
				if (bracketAtStack.size() <= 1) {
					codeblocks.push_back(TextBlock(bracketAtStack.top(), i));
				}
				bracketAtStack.pop();
			}
		}
	}
	//Add hotkeys
	// Hotkeys are formatted [Key Code 1] + [Key Code 2] + [Key Code 3] + ...
	// Where keycodes are case-insensitive https://github.com/IStrikeboomI/Hotkeyed/blob/master/HotKeyedLIB/src/keyboard/DeviceKeys.cpp
	// Ex: Ctrl + a + 2
	// Hotkeys are always before bracket either on same line or line above
	// All below are valid:
	/*
		[Hotkey] {

		}
		
		[Hotkey] 
		{

		}

		[Hotkey]




		{

		}

		[Hot
			+key]
			{

			}
	*/
	int prevBlockEnd = -1;
	for (TextBlock codeblock : codeblocks) {
		TextBlock hotkeyBlock = TextBlock(prevBlockEnd + 1, codeblock.start - 1);
		hotkeyBlocks.push_back(hotkeyBlock);
		std::string hotkey = script.substr(hotkeyBlock.start, hotkeyBlock.end - hotkeyBlock.start);
		hotkey = Util::replaceAll(hotkey,"\n","");
		hotkey = Util::replaceAll(hotkey, " ", "");
		//TODO: add way for hotkeys to have deviceId and key state
		//TODO: add way for hotkeys to have deviceId and key state
		//TODO: add way for hotkeys to have deviceId and key state
		std::vector<std::string> deviceKeys = Util::split(hotkey, "+");
		std::vector<Key> keys;
		for (std::string d : deviceKeys) {
			keys.push_back(DeviceKeys::getByName(d));
		}
		hotkeys.push_back(keys);
		prevBlockEnd = codeblock.end;
	}
	//Prints out script with colored portions for points of interest
	//Code blocks are in green
	//Hotkeys are in red
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < script.size();i++) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		for (TextBlock c : codeblocks) {
			if (i >= c.start && i <= c.end) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}
		}
		for (TextBlock c : hotkeyBlocks) {
			if (i >= c.start && i <= c.end) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			}
		}
		std::cout << script[i];
	}
	std::cout << "\n\n";
	for (Hotkey h : hotkeys) {
		for (Key k : h.keys) {
			std::cout << k.key << " ";
		}
		std::cout << "\n";
	}
	//Add hotkeys
	//Amount of hotkeys is equal to {} (LCB and RCB) pairs
	//int indexAt = 0;
	//for (int i = 0; i < std::min(LCBamount, RCBamount); i++) {
	//	int hotkeyStart = script.find('{', indexAt);
	//	
	//	std::string justHotkey = script.substr();
	//}
}
