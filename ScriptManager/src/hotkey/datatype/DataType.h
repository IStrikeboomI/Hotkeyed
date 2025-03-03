#pragma once
#include <string>
enum DataTypes {
	//VOID_E stands for void enum
	//not VOID because that's already defined by Windows.h
	VOID_E,
	//represented as long long int
	INTEGER,
	//represented as double
	FLOAT,
	//represented as std::string
	STRING
};
template <typename T>
class DataTypeImpl;
//Below class is needed to use various datatypes in a vector, acts like a wildcard
struct DataType { 
	virtual constexpr DataTypes getType() = 0;
	template<typename T>
	T* getData() const {
		return static_cast<DataTypeImpl<T>*>(this);
	}
};
template <typename T>
class DataTypeImpl : public DataType {	
public:
	T value;
	DataTypeImpl(const T& value) : value(value) {};
	virtual const T getDefaultValue() = 0;
	virtual const bool isValid(const std::string& text) = 0;
};
