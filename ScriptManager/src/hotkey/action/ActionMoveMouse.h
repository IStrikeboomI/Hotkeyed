#pragma once
#include <Windows.h>
#include "Action.h"
class ActionMoveMouse : public Action {
public:
	ActionMoveMouse();
	std::any execute(std::map<Parameter, std::any>& params) override;
};

