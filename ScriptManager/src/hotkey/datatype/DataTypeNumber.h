#pragma once
#include "DataType.h"
#include "../../lib/BigFloat/BigFloat.h"
class DataTypeNumber : public DataType {
public:
	const DataTypeNumber(const BigFloat& number) : DataType(number) {};
	const DataTypeNumber(const long long number) : DataType(BigFloat::BigFloat(number)) {};
	const DataTypeNumber(const std::string& number) : DataType(BigFloat::BigFloat(number)) {};
	constexpr DataTypes getType() override { return DataTypes::NUM; }
	const std::any getDefaultValue() override { return BigFloat::BigFloat(); };
};

