#include "Action.h"

Action::Action(const std::string_view& name, const DataTypes returnType, const std::vector<Parameter>& parameters, const std::string& description, const unsigned int actionCategories)
	: name(name), returnType(returnType), parameters(parameters), description(description), actionCategories(actionCategories) {
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

void Action::fillOptionalParameters(std::vector<std::shared_ptr<DataType>>& parameters) const {
	for (int i = this->parameters.size() - parameters.size(); i < parameters.size();i++) {
		if (this->parameters[i].optional) {
			DataTypes type = this->parameters[i].type;
			std::shared_ptr<DataType> defaultValue;
			switch (this->parameters[i].type) {

				case DataTypes::VOID_E: {
					defaultValue = std::make_shared<DataTypeVoid>(DataTypeVoid());
					break;
				}
				case DataTypes::INTEGER: {
					defaultValue = std::shared_ptr<DataTypeInteger>(this->parameters[i].defaultValue.getData<DataTypeInteger>());
					break;
				}
				case DataTypes::FLOAT: {
					defaultValue = std::shared_ptr<DataTypeFloat>(this->parameters[i].defaultValue.getData<DataTypeFloat>());
					break;
				}
				case DataTypes::STRING: {
					defaultValue = std::shared_ptr<DataTypeString>(this->parameters[i].defaultValue.getData<DataTypeString>());
					break;
				}
				default: {
					defaultValue = std::make_shared<DataTypeVoid>(DataTypeVoid());
					break;
				}	
			}
			parameters.push_back(defaultValue);
		}
	}
}
