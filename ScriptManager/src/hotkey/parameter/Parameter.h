#pragma once
#include <string>
#include <memory>
#include "../datatype/DataType.h"
#include "../datatype/DataTypeFloat.h"
#include "../datatype/DataTypeInteger.h"
#include "../datatype/DataTypeVoid.h"
#include "../datatype/DataTypeString.h"
//parameter to be held in a function or action
struct Parameter {
	const std::string name;
	const std::string description;
	const bool optional = false;
	const DataTypes type;
	const DataType& defaultValue;

	//this constructor should be used if parameter is not optional
	Parameter(
		const std::string& name,
		const DataTypes type,
		const std::string& description = "",
		const bool optional = false,
		const DataType& defaultValue = DataTypeVoid()
		) : name(name), type(type), description(description), optional(optional), defaultValue(defaultValue) {
	};
};
