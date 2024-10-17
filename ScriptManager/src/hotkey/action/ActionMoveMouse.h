#pragma once
#include <Windows.h>
#include "Action.h"
class ActionMoveMouse : public Action<ParameterVoid(),ParameterNum("x"), ParameterNum("y")> {
public:
	ActionMoveMouse();
	ParameterVoid execute() override;
};

