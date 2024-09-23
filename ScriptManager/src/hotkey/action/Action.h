#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "Parameter.h"

//Represents something to do inside a hotkey or function (ex. Make file, move mouse, click, etc.)
class Action {
public:
	const std::string returnValue;
	const std::string name;
	const std::vector<Parameter> parameters;

	Action(const std::string&& name, const std::vector<Parameter>&& possibleParameters, const std::string& returnValue = ParameterType::VOID);
	virtual std::any execute(std::map<Parameter,std::any>& params) = 0;

	static std::any getParam(const std::string& name, const std::map<Parameter, std::any>& params) {
		for (auto const& [key, val] : params) {
			if (key.name == name) {
				return val;
			}
		}
	}
};
