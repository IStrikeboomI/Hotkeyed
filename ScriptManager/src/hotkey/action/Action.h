#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "../parameter/Parameter.h"
#include "../parameter/ParameterNum.h"
#include "../../lib/BigFloat/BigFloat.h"

//Represents something to do inside a hotkey or function (ex. Make file, move mouse, click, etc.)
template <typename... P>
class Action {
public:
	const std::string returnValue;
	const std::string name;
	const std::vector<std::shared_ptr<Parameter<?>>> parameters;

	Action(const std::string_view& name, const int& returnValue = ParameterType::VOID_E);
	virtual std::any execute() = 0;

	 std::any getParam(const std::string& name, const std::map<Parameter, std::any>& params) {
		
		 for (auto const& [key, val] : params) {
			if (key.name == name) {
				return val;
			}
		}
	}
};
