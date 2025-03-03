#include "Action.h"
#include "ActionManager.h"
#include <memory>
#include <map>
//Holds an action with parameters that can later be called
//Just stores info, doesn't actually call, calling is handled by ScriptEngine
struct CallableAction {
	std::shared_ptr<Action> action;
	std::vector<std::shared_ptr<DataType>> parameters;
	CallableAction(const std::string& name, const std::vector<std::string>& parameters);
};