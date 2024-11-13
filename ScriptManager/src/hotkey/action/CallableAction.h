#include "Action.h"
#include "ActionManager.h"
#include "../../lib/BigFloat/BigFloat.h"
#include <memory>
#include <map>
//Holds an action with parameters that can later be called
//Just stores info, doesn't actually call, calling is handled by ScriptEngine
struct CallableAction {
	std::shared_ptr<Action> action;
	//CallableAction(const std::shared_ptr<Action>& action, const std::vector<Parameter> parameters);
	CallableAction(const std::string& name, const std::vector<std::string>& parameters);
};