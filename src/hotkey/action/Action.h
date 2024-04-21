#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "Parameter.h"

//Represents something to do inside a hotkey (ex. Make file, move mouse, click, etc.)
class Action {
public:
	const std::string name;
	const std::vector<Parameter> parameters;

	Action(const std::string&& name, const std::vector<Parameter>&& possibleParameters);
	virtual std::any execute(std::map<Parameter,std::any> params) = 0;

	static std::any getParam(std::string name, std::map<Parameter, std::any> params) {
		for (auto const& [key, val] : params) {
			if (key.name == name) {
				return val;
			}
		}
	}
};
