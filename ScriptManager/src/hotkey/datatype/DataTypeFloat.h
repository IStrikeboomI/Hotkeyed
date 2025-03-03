#pragma once
#include "DataType.h"
#include <Util.h>
class DataTypeFloat : public DataTypeImpl<double> {
public:
	DataTypeFloat(const std::string& text) : DataTypeImpl(std::stod(text)) {};
	DataTypeFloat(const double number) : DataTypeImpl(number) {};
	constexpr DataTypes getType() override { return DataTypes::FLOAT; }
	const double getDefaultValue() override { return 0; };
	const bool isValid(const std::string& text) override { return false; };
};

