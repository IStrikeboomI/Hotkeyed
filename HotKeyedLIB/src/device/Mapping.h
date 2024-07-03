#pragma once
#include <string>
#include <fstream>
class Mapping {
private:
	std::ofstream mapping;
public:
	Mapping(std::string filename="mapping.mapping");

};

