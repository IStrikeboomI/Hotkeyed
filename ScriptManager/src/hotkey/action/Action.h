#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "../../lib/BigFloat/BigFloat.h"
#include "../parameter/Parameter.h"
//Represents something to do inside a hotkey or function (ex. Make file, move mouse, click, etc.)
class Action {
public:
	const std::string name;
	const std::vector<Parameter> parameters;
	const DataTypes returnType;
	const std::string description;

	Action(const std::string_view& name, const DataTypes returnType = DataTypes::VOID_E,const std::vector<Parameter>& parameters = std::vector<Parameter>(),const std::string& description = "");
	bool areParametersValid(const std::vector<std::shared_ptr<DataType>>& parameters) const;
	virtual DataType execute() = 0;

};
