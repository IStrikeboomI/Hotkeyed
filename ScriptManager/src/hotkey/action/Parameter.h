#pragma once
#include <string>
struct Parameter {
public:
	std::string type;
	std::string name;
	std::string description;
	bool optional = false;

	Parameter(const std::string_view& type,
			  const std::string&& name,
			  const std::string&& description = "",
			  const bool optional = false) : type(type), name(name), description(description), optional(optional) {};
	bool operator<(const Parameter& p) const {
		return type < p.type;
	}
};
namespace ParameterType {
	constexpr std::string_view ANY = "any";
	//int is the big int library in the lib folder
	constexpr std::string_view INT = "int";
	constexpr std::string_view STRING = "string";
	constexpr std::string_view VOID_S = "void";
};