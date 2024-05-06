#include "ActionManager.h"

ActionManager::ActionManager() {

}
ActionManager& ActionManager::getInstance() {
	static ActionManager instance;
	return instance;
}
