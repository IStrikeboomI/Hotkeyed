#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include "../Util.h"
#include <map>
#include "../../lib/json/json.hpp"

class Mapping {
private:
	std::string filename;
	std::fstream file;
	nlohmann::json json;
public:
	std::map<std::string, int> mapping;

	Mapping(std::string filename="mapping.mapping");
	//Mapping(const Mapping&) = default;

	void saveMapping();
	void applyMapping();
};

