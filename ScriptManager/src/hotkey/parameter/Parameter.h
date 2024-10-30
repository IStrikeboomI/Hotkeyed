#pragma once
#include <string>
#include "../datatype/DataType.h"
struct Parameter {
public:
	std::string name;
	std::string description;
	bool optional = false;
	
	template <typename T>
	constexpr Parameter(
		const std::string_view& name,
		const std::string_view&& description = "",
		const bool optional = false,
		const T& defaultValue = T.getDefaultValue()
		) : name(name), description(description), optional(optional) {
		
	};
};
