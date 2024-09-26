#include "ActionManager.h"

ActionManager::ActionManager() {
	actions.push_back(std::make_shared<ActionPrint>(ActionPrint()));
	actions.push_back(std::make_shared<ActionMoveMouse>(ActionMoveMouse()));
	actions.push_back(std::make_shared<ActionRand>(ActionRand()));
}
ActionManager& ActionManager::getInstance() {
	static ActionManager instance;
	return instance;
}
