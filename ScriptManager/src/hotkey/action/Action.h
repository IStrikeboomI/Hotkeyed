#pragma once
#include <vector>
#include <map>
#include <string>
#include <any>
#include "BigFloat/BigFloat.h"
#include "../parameter/Parameter.h"
enum ActionCategories {
	CATEGORY_MISC = 1 << 1,
	CATEGORY_KEYBOARD = 1 << 2,
	CATEGORY_MOUSE = 1 << 3,
	CATEGORY_MATH = 1 << 4,
	CATEGORY_DEBUG = 1 << 5
};
//Represents something to do inside a hotkey or function (ex. Make file, move mouse, click, etc.)
class Action {
public:
	//bitmask of action categories where it gets shifted by the enum value
	unsigned int actionCategories;
	const std::string name;
	const std::vector<Parameter> parameters;
	const DataTypes returnType = DataTypes::VOID_E;
	const std::string description;

	Action(const std::string_view& name, 
		   const DataTypes returnType = DataTypes::VOID_E,
		   const std::vector<Parameter>& parameters = std::vector<Parameter>(),
		   const std::string& description = "",
		   const unsigned int actionCategories = 1);
	//checks if parameters passed into an action can match with the parameters needed
	//checks by seeing if all non-optional parameters are passed and if all the parameters passed match the datatype
	bool areParametersValid(const std::vector<std::shared_ptr<DataType>>& parameters) const;
	//adds the default value for optional parameters that are left empty
	void fillOptionalParameters(std::vector<std::shared_ptr<DataType>>& parameters) const;
	virtual std::shared_ptr<DataType> execute(std::vector<std::shared_ptr<DataType>>& parameters) = 0;

};
