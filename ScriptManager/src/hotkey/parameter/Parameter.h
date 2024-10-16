#pragma once
#include <string>
template <typename T>
struct Parameter {
public:
	std::string name;
	std::string description;
	bool optional = false;
	T value = getDefaultValue();
	
	Parameter(const std::string_view& type,
			  const std::string&& name,
			  const std::string&& description = "",
			  const bool optional = false) : name(name), description(description), optional(optional) {};

	virtual constexpr int getType() = 0;
	virtual constexpr T getDefaultValue() = 0;
};
enum ParameterType {
	VOID_E,
	NUM,
	STRING
};