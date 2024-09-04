#include "ActionPrint.h"

ActionPrint::ActionPrint() : Action("Print", {Parameter(ParameterType::STRING,"text")}) {
}

std::any ActionPrint::execute(std::map<Parameter, std::any>& params) {
	std::cout << std::any_cast<std::string>(getParam("text",params));
	return std::any();
}
