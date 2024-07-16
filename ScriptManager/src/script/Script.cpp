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
	//add all bracket pairs
	std::stack<int> bracketAtStack;
	for (int i = 0; i < script.size();i++) {
		if (script[i] == '{') {
			bracketAtStack.push(i);
		}
		if (script[i] == '}') {
			if (!bracketAtStack.empty()) {
				codeblocks.push_back(CodeBlock(bracketAtStack.top(), i));
				bracketAtStack.pop();
			}
		}
	}
	for (CodeBlock c : codeblocks) {
		std::cout << c << "\n";
		std::cout << script[c.start] << " " << script[c.end] << "\n";
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
