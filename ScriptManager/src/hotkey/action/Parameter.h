#pragma once
#include <string>
struct Parameter {
public:
	std::string type;
	std::string name;
	std::string description;
	bool optional = false;

	Parameter(const std::string& type,
			  const std::string&& name,
			  const std::string&& description = "",
			  const bool optional = false) : type(type), name(name), description(description), optional(optional) {};
};
namespace ParameterType {
	const std::string ANY = "any";
	const std::string INT = "int";
	const std::string STRING = "string";
};