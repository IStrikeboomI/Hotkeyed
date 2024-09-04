#pragma once
#include <iostream>
#include "Action.h"
class ActionPrint : public Action{
public:
	ActionPrint();
	std::any execute(std::map<Parameter, std::any>& params) override;
};

