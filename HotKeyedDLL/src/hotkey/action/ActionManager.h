#pragma once
#include <vector>
#include <memory>
#include "Action.h"
class ActionManager {
private:
	std::vector<std::shared_ptr<Action>> actions;
	//private constructor because singleton
	ActionManager();
public:
	static ActionManager& getInstance();

	//don't implement these two or else we might get multiple copies
	ActionManager(const ActionManager&) = delete;
	void operator=(const ActionManager&) = delete;
};

