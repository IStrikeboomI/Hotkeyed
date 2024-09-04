#include "ScriptFunction.h"

ScriptFunction::ScriptFunction(const std::string& name, const std::vector<Parameter> parameters) : name(name), parameters(parameters) {
}

std::any ScriptFunction::execute() {
	return std::any();
}
