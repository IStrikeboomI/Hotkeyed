#pragma once
#include <any>
class DataType {	
public:
	std::any value = getDefaultValue();
	DataType(const std::any& value) : value(value) {};
	virtual constexpr DataTypes getType() = 0;
	virtual const std::any getDefaultValue() = 0;
};
enum DataTypes {
	//VOID_E stands for void enum
	//not VOID because that's already defined by Windows.h
	VOID_E,
	NUM,
	STRING
};