#include "Print.h"

Print::Print() : Action("Print", {Parameter(ParameterType::STRING,"text")}) {
}

std::any Print::execute(std::map<Parameter, std::any>& params) {
	std::cout << std::any_cast<std::string>(getParam("text",params));
	return std::any();
}
