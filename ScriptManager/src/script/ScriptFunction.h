#pragma once
#include <vector>
#include <any>
#include <string>
#include "../hotkey/action/Parameter.h"
class ScriptFunction {
private:
	std::string name;
	//parameter type is ALWAYS any, description is empty, optional is false
	std::vector<Parameter> parameters;
public:
	ScriptFunction(std::string& name, std::vector<Parameter> parameters);
	//runs function and returns value
	std::any execute();

};

