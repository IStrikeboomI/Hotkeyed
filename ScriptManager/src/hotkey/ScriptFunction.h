#pragma once
#include <vector>
#include <any>
#include <string>
#include "../hotkey/parameter/Parameter.h"

//Function used inside the script
class ScriptFunction {
private:
	std::string name;
	//parameter type is ALWAYS any, description is empty, optional is false
	std::vector<Parameter> parameters;
public:
	ScriptFunction(const std::string& name, const std::vector<Parameter> parameters);
	//runs function and returns value
	std::any execute();

};

