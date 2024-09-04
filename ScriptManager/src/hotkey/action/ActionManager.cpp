#include "ActionManager.h"

ActionManager::ActionManager() {
	actions.push_back(std::make_shared<ActionPrint>(ActionPrint()));
	actions.push_back(std::make_shared<ActionMoveMouse>(ActionMoveMouse()));
}
ActionManager& ActionManager::getInstance() {
	static ActionManager instance;
	return instance;
}
