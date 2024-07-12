#include "Script.h"

Script::Script(const std::string& filename) : filename(filename) {
	std::ifstream file(filename);
	std::string str;
	while (std::getline(file,str)) {
		script += str + "\n";
	}
	std::cout << script << "\n";

	int LCBamount = std::ranges::count(script, '{');
	int RCBamount = std::ranges::count(script, '}');

	//Add hotkeys
	//Amount of hotkeys is equal to {} (LCB and RCB) pairs
	int indexAt = 0;
	for (int i = 0; i < std::min(LCBamount, RCBamount); i++) {
		int hotkeyStart = script.find('{', indexAt);
		
		std::string justHotkey = script.substr();
	}
}
