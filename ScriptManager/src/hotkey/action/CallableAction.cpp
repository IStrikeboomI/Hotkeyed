#include "CallableAction.h"

//CallableAction::CallableAction(const std::shared_ptr<Action>& action, const std::map<Parameter, std::any>& parameters) : action(action), parameters(parameters) {
//}

CallableAction::CallableAction(const std::string& name, const std::vector<std::string>& parameters) {
	for (std::shared_ptr<Action> a : ActionManager::getInstance().actions) {
		if (a->name == name) {
			this->action = a;
		}
	}
	//Convert provided parameters into datatype for the action to use
	std::vector<std::shared_ptr<DataType>> formattedParameters(parameters.size());
	for (int i = 0; i < parameters.size();i++) {
		std::shared_ptr<DataType> data = std::make_shared<DataTypeVoid>(DataTypeVoid());
		if (this->action->parameters[i].type == DataTypes::INTEGER_E) {
			data = std::make_shared<DataTypeInteger>(DataTypeInteger(parameters[i]));
		}  
		if (this->action->parameters[i].type == DataTypes::FLOAT_E) {
			data = std::make_shared<DataTypeFloat>(DataTypeFloat(parameters[i]));
		}
		if (this->action->parameters[i].type == DataTypes::STRING_E) {
			data = std::make_shared<DataTypeString>(DataTypeString(parameters[i]));
		}
		formattedParameters[i] = data;
		std::cout << parameters[i] << "\n";
	}
	this->action->fillOptionalParameters(formattedParameters);
	//See if provided parameters can work with the parameters that action expects
	if (this->action->areParametersValid(formattedParameters)) {
		this->parameters = formattedParameters;
		for (std::shared_ptr<DataType> d: this->parameters) {
			//std::cout << d->value << "\n";
		}
	}
	
	
}
