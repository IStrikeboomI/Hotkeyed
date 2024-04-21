#pragma once
#include <string>
struct Parameter {
public:
	ParameterType type;
	std::string name;
	std::string description;
	bool optional = false;

	Parameter(ParameterType type,
			  std::string name,
			  std::string description = "",
			  bool optional = false) : type(type), name(name), description(description), optional(optional) {};
};
enum ParameterType {
	INT,
	STRING,
};