#pragma once
#include <string>
template <typename T>
struct Parameter {
public:
	std::string name;
	std::string description;
	bool optional = false;
	T value = getDefaultValue();
	
	constexpr Parameter(
		      constexpr std::string_view& name,
			  const std::string& description = "",
			  const bool optional = false) : name(name), description(description), optional(optional) {};

	virtual constexpr int getType() = 0;
	virtual constexpr T getDefaultValue() = 0;
};
enum ParameterType {
	//VOID_E stands for void enum
	//not VOID because that's already defined by Windows.h
	VOID_E,
	NUM,
	STRING
};