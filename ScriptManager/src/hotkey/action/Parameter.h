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
	//num is the big float library in the lib folder
	constexpr std::string_view NUM = "num";
	constexpr std::string_view STRING = "string";
	//Not VOID because thats already defined somewhere
	constexpr std::string_view VOID_S = "void";
};