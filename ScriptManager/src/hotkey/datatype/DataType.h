#pragma once
#include <any>
enum DataTypes {
	//VOID_E stands for void enum
	//not VOID because that's already defined by Windows.h
	VOID_E,
	//represented as BigFloat in the lib folder
	NUM,
	//represented as std::string
	STRING
};
class DataType {	
public:
	std::any value = getDefaultValue();
	DataType(const std::any& value) : value(value) {};
	virtual constexpr DataTypes getType() = 0;
	virtual const std::any getDefaultValue() = 0;
	template <typename T>
	const T getValue() const {
		return std::any_cast<T>(this->value);
	};
};
