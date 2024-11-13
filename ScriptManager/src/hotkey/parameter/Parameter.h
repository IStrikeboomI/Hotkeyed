#pragma once
#include <string>
#include <memory>
#include "../datatype/DataType.h"
#include "../datatype/DataTypeNumber.h"
#include "../datatype/DataTypeVoid.h"
struct Parameter {
	const std::string name;
	const std::string description;
	const bool optional = false;
	const DataTypes type;
	std::shared_ptr<DataType> defaultValue;

	//this constructor should be used if parameter is not optional
	const Parameter(
		const std::string& name,
		const DataTypes type,
		const std::string& description = "",
		const bool optional = false,
		const std::unique_ptr<DataType> defaultValue;
		) : name(name), type(type), description(description), optional(optional), defaultValue() {
	};
};
