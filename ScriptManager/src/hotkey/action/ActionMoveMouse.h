#pragma once
#include <Windows.h>
#include "Action.h"
class ActionMoveMouse : public Action {
public:
	ActionMoveMouse();
	std::shared_ptr<DataType> execute(std::vector<std::shared_ptr<DataType>>& parameters) override;
};

