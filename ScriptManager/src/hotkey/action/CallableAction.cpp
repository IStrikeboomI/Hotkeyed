#include "Action.h"
#include <memory>
//Holds an action with parameters that can later be called
//Just stores info, doesn't actually call, calling is handled by ScriptEngine
struct CallableAction {
	std::shared_ptr<Action> action;
	std::vector<Parameter> parameters;
	CallableAction(const std::string& name, const std::vector<std::string>& parameters) {

	}
};