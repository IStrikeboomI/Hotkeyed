#pragma once
#include <iostream>
#include <random>
#include "Action.h"
class ActionRand : public Action {
public:
	ActionRand();
	std::shared_ptr<DataType> execute(std::vector<std::shared_ptr<DataType>>& parameters) override;
};

