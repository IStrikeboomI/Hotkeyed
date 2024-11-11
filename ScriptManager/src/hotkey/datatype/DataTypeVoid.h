#include "DataType.h"
class DataTypeVoid : public DataType {
public:
	const DataTypeVoid() : DataType(0) {};
	constexpr DataTypes getType() override { return DataTypes::VOID_E; }
	const std::any getDefaultValue() override { return 0; };
};