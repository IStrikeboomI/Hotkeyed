#pragma once
#include <string>
#include <memory>
#include "../datatype/DataType.h"
#include "../datatype/DataTypeNumber.h"
#include "../datatype/DataTypeVoid.h"
#include "../datatype/DataTypeString.h"
struct Parameter {
	const std::string name;
	const std::string description;
	const bool optional = false;
	const DataTypes type;
	const DataType& defaultValue;

	//this constructor should be used if parameter is not optional
	const Parameter(
		const std::string& name,
		const DataTypes type,
		const std::string& description = "",
		const bool optional = false,
		const DataType& defaultValue = DataTypeVoid()
		) : name(name), type(type), description(description), optional(optional), defaultValue(defaultValue) {
	};
};
