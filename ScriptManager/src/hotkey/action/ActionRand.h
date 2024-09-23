#pragma once
#include <iostream>
#include <random>
#include "Action.h"
class ActionRand : public Action {
public:
	ActionRand();
	std::any execute(std::map<Parameter, std::any>& params) override;
};

