#include "Script.h"

bool Script::isIndexInGlobal(int index) {
	for (TextBlock b : codeblocks) {
		if (b.withinInclusive(index)) {
			return false;
		}
	}
	for (TextBlock b : functionBlocks) {
		if (b.withinInclusive(index)) {
			return false;
		}
	}
	for (TextBlock b : hotkeyBlocks) {
		if (b.withinInclusive(index)) {
			return false;
		}
	}
	for (TextBlock b : squareBracketBlocks) {
		if (b.withinInclusive(index)) {
			return false;
		}
	}
	return true;
}

Script::Script(const std::string& filename) : filename(filename) {
	std::ifstream file(filename);
	std::string line;
	while (std::getline(file, line)) {
		//ignore lines that start with "//" because that signifies a comment
		if (!line.starts_with("//")) {
			script += line + "\n";
		}
	}
	//Add all isolated bracket pairs
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
	int squareBracketAt = -1;
	for (int i = 0; i < script.size(); i++) {
		if (script[i] == '[' && squareBracketAt == -1) {
			squareBracketAt = i;
		}
		if (script[i] == ']' && squareBracketAt != -1) {
			squareBracketBlocks.push_back(TextBlock(squareBracketAt, i));
			squareBracketAt = -1;
		}
	}
	
	//Add hotkeys
	// Hotkeys are formatted [Key Code 1] + [Key Code 2] + [Key Code 3] + ...
	// Where keycodes are case-insensitive https://github.com/IStrikeboomI/Hotkeyed/blob/master/HotKeyedLIB/src/keyboard/DeviceKeys.cpp
	// Ex: Ctrl + a + 2
	// Hotkeys are always in square brackets and before bracket either on same line or line below;
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
	for (TextBlock squareBracketBlock : squareBracketBlocks) {
		TextBlock hotkeyBlock = TextBlock(squareBracketBlock.start + 1, squareBracketBlock.end - 1);
		hotkeyBlocks.push_back(hotkeyBlock);

		std::string hotkey = script.substr(hotkeyBlock.start, hotkeyBlock.end - hotkeyBlock.start);
		//remove spaces and new lines
		hotkey = Util::replaceAll(hotkey,"\n","");
		hotkey = Util::replaceAll(hotkey, " ", "");
		//split keys by each plus sign
		std::vector<std::string> deviceKeys = Util::split(hotkey, "+");
		std::vector<Key> keys;
		for (std::string d : deviceKeys) {
			//checks if key provided has parameters in parentheses after key ex. k (DOWN, !10-20)
			if (d.find("(") != std::string::npos && d.find(")") != std::string::npos && d.find_last_of("(") < d.find_last_of(")")) {
				int openingParentheses = d.find_last_of("(");
				int closingParentheses = d.find_last_of(")");
				std::string paramString = d.substr(openingParentheses + 1, closingParentheses - openingParentheses - 1);
				std::vector<std::string> params = Util::split(paramString, ",");

				KEYSTATE state = KEYSTATE::DOWN;
				std::vector<DeviceIDRule> deviceIdRules;
				for (std::string p : params) {
					if (Util::caseInsensitiveEquals(p,"down")) {
						state = KEYSTATE::DOWN;
					}
					if (Util::caseInsensitiveEquals(p, "up")) {
						state = KEYSTATE::UP;
					}
					bool hasDeviceIdParam = false;
					bool exclude = false;
					unsigned int start = std::numeric_limits<unsigned int>::max(), end = std::numeric_limits<unsigned int>::max();
					//means number without range is parameter
					if (p.find("-") == std::string::npos) {
						if (p[0] == '!') {
							exclude = true;
							p = p.substr(1,p.length() - 1);
						}
						if (Util::isNumber(p)) {
							start = std::stoi(p);
							end = std::stoi(p);
							hasDeviceIdParam = true;
						}
					} else {
						//has range
						if (p[0] == '!') {
							exclude = true;
							p = p.substr(1, p.length() - 1);
						}
						int minus = p.find_first_of("-");
						std::string firstNum = p.substr(0, minus);
						std::string secondNum = p.substr(minus + 1, p.length());
						if (Util::isNumber(firstNum) && Util::isNumber(secondNum)) {
							start = std::stoi(firstNum);
							end = std::stoi(secondNum);
							hasDeviceIdParam = true;
						}
					}
					if (hasDeviceIdParam) {
						deviceIdRules.push_back(DeviceIDRule(start, end, exclude));
					}
				}
				std::string key = d.substr(0,openingParentheses);
				if (DeviceKeys::getByName(key).value != 0) {
					keys.push_back(Key(DeviceKeys::getByName(key), state, deviceIdRules));
				}
			} else {
				if (DeviceKeys::getByName(d).value != 0) {
					keys.push_back(DeviceKeys::getByName(d));
				}
			}
		}
		hotkeys.push_back(keys);
	}

	//Characters that can't be the starting character(s) for a function, variable, or parameter
	static const std::set<std::string> ineligibleStartingCharacters = {
		"[",
		"]",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"0",
		"+"
	};
	
	//Add functions
	std::string functionScriptCopy = script;
	int functionScriptCopyAt = 0;
	while (functionScriptCopy.find("function") != std::string::npos) {
		int functionLocation = functionScriptCopy.find("function");
		functionScriptCopy = functionScriptCopy.substr(functionLocation);
		functionScriptCopyAt += functionLocation;
		int nextParentheses = functionScriptCopy.find("(");
		int nextBracket = functionScriptCopy.find("{");
		int nextClosingBracket = functionScriptCopy.find("}");
		if (functionLocation < nextParentheses && functionLocation < nextBracket) {
			if (nextBracket > nextParentheses) {
				functionBlocks.push_back(TextBlock(functionScriptCopyAt + functionLocation, functionScriptCopyAt + nextBracket));
				functionScriptCopy = functionScriptCopy.substr(nextClosingBracket);
				functionScriptCopyAt += nextClosingBracket;
			}
		}
	}
	//Add global statements
	for (int i = 0; i < script.length();i++) {
		//skip over all the blocks, then we are working with only global lines
		if (isIndexInGlobal(i)) {
			std::cout << i << "\n";
			int nextSemiColon = script.find(";", i+1);
			if (nextSemiColon != std::string::npos && isIndexInGlobal(nextSemiColon)) {
				globalLines.push_back(TextBlock(i, nextSemiColon));
				i = nextSemiColon + 1;
			} else {
				//TODO throw error
			}
		}
	}

	std::cout << "\n";
	std::cout << "------------------------------------" << "\n";
	std::cout << "             Marked Script          " << "\n";
	std::cout << "------------------------------------" << "\n";
	std::cout << "\n";
	//Prints out script with colored portions for points of interest
	//Code blocks are in green
	//Hotkeys are in red
	//Global Lines are in blue
	//Functions are in purple
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < script.size(); i++) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
		for (TextBlock c : codeblocks) {
			if (c.withinInclusive(i)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
			}
		}
		for (TextBlock c : hotkeyBlocks) {
			if (c.withinInclusive(i)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
			}
		}
		for (TextBlock c : globalLines) {
			if (c.withinInclusive(i)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE);
			}
		}
		for (TextBlock c : functionBlocks) {
			if (c.withinInclusive(i)) {
				SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED);
			}
		}
		std::cout << script[i];
	}
	std::cout << "\n\n";
	for (Hotkey h : hotkeys) {
		for (Key k : h.keys) {
			std::cout << k.deviceIDs.size() << " ";
		}
	}
	std::cout << "\n";
}
