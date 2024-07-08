#include "Script.h"

Script::Script(const std::string& filename) : filename(filename) {
	std::ifstream file(filename);
	std::string str;
	while (std::getline(file,str)) {
		std::cout << str << "\n";
	}
}
