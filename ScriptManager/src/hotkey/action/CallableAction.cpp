#include "CallableAction.h"

//allableAction::CallableAction(const std::shared_ptr<Action>& action, const std::map<Parameter, std::any>& parameters) : action(action), parameters(parameters) {
//}

CallableAction::CallableAction(const std::string& name, const std::vector<std::string>& parameters) {
	for (std::shared_ptr<Action> a : ActionManager::getInstance().actions) {
		if (a->name == name) {
			this->action = a;
		}
	}
	//See if provided parameters can work with the parameters that action expects
	for (int i = 0; i < action->parameters.size();i++) {
		Parameter expected = action->parameters[i];
		if (!expected.optional) {
			if (parameters.size() <= i) {
				//TODO throw error here because provided parameters is smaller than expected
			}
		}
		std::any parameterValue = 0;
		//if (expected.type == ParameterType::ANY || expected.type.empty()) {
		//	parameterValue = parameters[i];
		//}
		//if (expected.type == ParameterType::STRING) {
		//	parameterValue = parameters[i];
		//}
		//if (expected.type == ParameterType::NUM) {
		//	parameterValue = BigFloat(parameters[i]);
		//}
		//this->parameters.emplace(expected, parameterValue);
	}
}
