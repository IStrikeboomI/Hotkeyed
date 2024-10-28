#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "../../lib/BigFloat/BigFloat.h"

//Represents something to do inside a hotkey or function (ex. Make file, move mouse, click, etc.)
//R is the return type and P is a list of parameters
template <Parameter R, Parameter... P>
class Action {
public:
	const std::string name;
	const std::vector<std::shared_ptr<P...>> parameters;

	Action(const std::string_view& name);
	virtual R execute() = 0;

	 std::any getParam(const std::string& name, const std::map<Parameter, std::any>& params) {
		
		 for (auto const& [key, val] : params) {
			if (key.name == name) {
				return val;
			}
		}
	}
};
