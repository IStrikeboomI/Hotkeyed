#pragma once
#include "DataType.h"
#include "../../lib/BigFloat/BigFloat.h"
class DataTypeNumber : public DataType {
public:
	constexpr DataTypeNumber(const std::string& number) : DataType(BigFloat::BigFloat(number)) {};
	constexpr DataTypes getType() override { return DataTypes::NUM; }
	const std::any getDefaultValue() override { return BigFloat::BigFloat(); };
};

