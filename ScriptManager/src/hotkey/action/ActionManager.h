#pragma once
#include <vector>
#include <memory>
#include "Action.h"

#include "ActionPrint.h"
#include "ActionMoveMouse.h"
#include "ActionRand.h"
class ActionManager {
private:	
	//private constructor because singleton
	ActionManager();
public:
	std::vector<std::shared_ptr<Action>> actions;

	static ActionManager& getInstance();

	//don't implement these two or else we might get multiple copies
	ActionManager(const ActionManager&) = delete;
	void operator=(const ActionManager&) = delete;
};

