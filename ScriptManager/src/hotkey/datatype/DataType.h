#pragma once
//D is type T that is the default value
template <typename T,T D>
class DataType {
private:
	T value = D;
public:
	public DataType(T& value) : value(value) {};
	virtual constexpr int getType() = 0;
	constexpr T getDefaultValue() final { return D; };
};
enum DataTypes {
	//VOID_E stands for void enum
	//not VOID because that's already defined by Windows.h
	VOID_E,
	NUM,
	STRING
};