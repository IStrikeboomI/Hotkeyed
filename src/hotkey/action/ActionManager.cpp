#include "ActionManager.h"

ActionManager& ActionManager::getInstance() {
	static ActionManager instance;
	return instance;
}
