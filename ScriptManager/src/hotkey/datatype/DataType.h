#pragma once
//D is type T that is the default value
template <typename T>
class DataType {	
public:
	T value = getDefaultValue();
	constexpr DataType(const T& value = getDefaultValue()) : value(value) {};
	virtual constexpr int getType() = 0;
	virtual constexpr T getDefaultValue() = 0;
};
enum DataTypes {
	//VOID_E stands for void enum
	//not VOID because that's already defined by Windows.h
	VOID_E,
	NUM,
	STRING
};