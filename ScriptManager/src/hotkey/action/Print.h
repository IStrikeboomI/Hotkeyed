#pragma once
#include <iostream>
#include "Action.h"
class Print : public Action{
public:
	Print();
	std::any execute(std::map<Parameter, std::any>& params) override;
};

