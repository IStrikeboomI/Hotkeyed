#include "Action.h"

Action::Action(const std::string_view& name, const DataTypes returnType, const std::vector<Parameter>& parameters, const std::string& description)
	: name(name), returnType(returnType), parameters(parameters), description(description) {
}

bool Action::areParametersValid(const std::vector<std::shared_ptr<DataType>>& parameters) const {
	//provided too many parameters
	if (parameters.size() > this->parameters.size()) {
		return false;
	}
	//go over every expected parameter to see if it works
	for (int i = 0; i < this->parameters.size();i++) {
		Parameter expected = this->parameters[i];
		if (!expected.optional) {
			//if provided parameter is not sent that it means its smaller then the index of the first optional 
			if (parameters.size() < i) {
				return false;
			}
		} else {
			//if not enough passed parameter but it is optional then the rest should all be fine
			if (parameters.size() < i) {
				return true;
			}
		}
		//check if they are same type
		std::shared_ptr<DataType> passed = parameters[i];
		if (expected.type != passed->getType()) {
			return false;
		}
	}
	return true;
}
