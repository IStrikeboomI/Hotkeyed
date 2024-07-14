#include "Script.h"

Script::Script(const std::string& filename) : filename(filename) {
	std::ifstream file(filename);
	std::string str;
	while (std::getline(file,str)) {
		//ignore lines that start with "//" because that signifies a comment
		if (!str.starts_with("//")) {
			script += str + "\n";
		}
	}
	std::cout << script << "\n";

	for (int i = 0; i < str.size();i++) {

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
