#pragma once
#include <Windows.h>
#include "Action.h"
class MoveMouse : public Action {
public:
	MoveMouse();
	std::any execute(std::map<Parameter, std::any> params) override;
};

