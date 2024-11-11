#pragma once
#include <iostream>
#include "Action.h"
class ActionPrint : public Action{
public:
	ActionPrint();
	std::shared_ptr<DataType> execute(std::vector<std::shared_ptr<DataType>>& parameters) override;
};

