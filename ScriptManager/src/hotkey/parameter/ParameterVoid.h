#pragma once
#include "Parameter.h"
#include <type_traits>
//not really meant as a parameter, meant to be used a return type
class ParameterVoid : public Parameter<void> {
public:
	constexpr ParameterVoid() : Parameter("") {};
	constexpr int getType() override;
	constexpr void getDefaultValue() override;
};

