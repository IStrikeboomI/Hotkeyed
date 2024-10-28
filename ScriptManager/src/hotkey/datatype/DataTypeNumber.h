#pragma once
#include "DataType.h"
#include "../../lib/BigFloat/BigFloat.h"
class DataTypeNumber : public DataType<BigFloat,BigFloat::BigFloat()> {
	virtual constexpr int getType() override { return DataTypes::NUM; };
};

