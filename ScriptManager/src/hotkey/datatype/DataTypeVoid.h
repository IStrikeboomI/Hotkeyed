#include "DataType.h"
#include <any>
class DataTypeVoid : public DataTypeImpl<std::any> {
public:
	DataTypeVoid() : DataTypeImpl(0) {};
	constexpr DataTypes getType() override { return DataTypes::VOID_E; }
	const std::any getDefaultValue() override { return 0; };

	const bool isValid(const std::string& text) override {
		return true;
	}
};