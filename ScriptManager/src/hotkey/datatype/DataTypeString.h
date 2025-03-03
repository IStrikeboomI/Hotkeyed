#pragma once
#include "DataType.h"
#include <string>
#include <Util.h>
class DataTypeString : public DataTypeImpl<std::string> {
public:
	DataTypeString(const std::string& text) : DataTypeImpl(text) {};
	DataTypeString(const long long number) : DataTypeImpl(std::to_string(number)) {};
	constexpr DataTypes getType() override { return DataTypes::STRING; }
	const std::string getDefaultValue() override { return ""; };

	const bool isValid(const std::string& text) override { return true; };

};

