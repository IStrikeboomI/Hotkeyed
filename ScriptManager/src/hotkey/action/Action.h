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
	const DataTypes returnType = DataTypes::VOID_E;
	const std::string description;

	Action(const std::string_view& name, const DataTypes returnType = DataTypes::VOID_E,const std::vector<Parameter>& parameters = std::vector<Parameter>(),const std::string& description = "");
	//checks if parameters passed into an action can match with the parameters needed
	//checks by seeing if all non-optional parameters are passed and if all the parameters passed match the datatype
	bool areParametersValid(const std::vector<std::shared_ptr<DataType>>& parameters) const;
	//adds the default value for optional parameters that are left empty
	void fillOptionalParameters(std::vector<std::shared_ptr<DataType>>& parameters) const;
	virtual DataType execute() = 0;

};
