#pragma once
#include "DataType.h"
#include <string>
#include <Util.h>
#include "../../lib/BigFloat/BigFloat.h"
class DataTypeString : public DataType {
public:
	const DataTypeString(const std::string& text) : DataType(text) {};
	const DataTypeString(const BigFloat& number) : DataType(number.toString()) {};
	const DataTypeString(const long long number) : DataType(std::to_string(number)) {};
	constexpr DataTypes getType() override { return DataTypes::STRING; }
	const std::any getDefaultValue() override { return ""; };
};

