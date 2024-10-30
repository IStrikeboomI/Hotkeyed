#pragma once
#include "DataType.h"
#include "../../lib/BigFloat/BigFloat.h"
class DataTypeNumber : public DataType<BigFloat> {
public:
	constexpr DataTypeNumber(const std::string& number) : DataType(BigFloat::BigFloat(number)) {};
	constexpr int getType() override { return DataTypes::NUM; }
	constexpr BigFloat getDefaultValue() override { return BigFloat::BigFloat(); };
};

