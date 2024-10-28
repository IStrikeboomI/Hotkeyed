#pragma once
#include <string>
#include "../datatype/DataType.h"
template <DataType T>
struct Parameter {
public:
	std::string name;
	std::string description;
	bool optional = false;
	
	constexpr Parameter(
		constexpr std::string_view& name,
		constexpr std::string_view&& description = "",
		constexpr bool optional = false,
		constexpr T defaultValue 
		) : name(name), description(description), optional(optional) {
		
	};
};
