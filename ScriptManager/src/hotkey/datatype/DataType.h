#pragma once
#include <string>
//**_E stands for  enum because some are already defined by Windows.h

enum DataTypes {
	VOID_E,
	//represented as long long int
	INTEGER_E,
	//represented as double
	FLOAT_E,
	//represented as std::string
	STRING_E
};
template <typename T>
class DataTypeImpl;
//Below class is needed to use various datatypes in a vector, acts like a wildcard
struct DataType { 
	virtual constexpr DataTypes getType() = 0;
	template<typename T>
	const T* getData() const {
		return static_cast<const T*>(this);
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
