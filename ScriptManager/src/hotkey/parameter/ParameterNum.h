#pragma once
#include "Parameter.h"
#include "../../lib/BigFloat/BigFloat.h"
#include "../../../lib/BigFloat/BigFloat.h"
class ParameterNum : public Parameter<BigFloat> {
public:
	constexpr ParameterNum(
				 constexpr std::string& name,
				 const std::string_view&& description = "",
				 const bool optional = false) : Parameter(name,"",false) { };
	constexpr int getType() override;
	constexpr BigFloat getDefaultValue() override;
};

