#pragma once
#include "Parameter.h"
#include "../../lib/BigFloat/BigFloat.h"
class ParameterNum : public Parameter<BigFloat> {
public:
	constexpr ParameterNum(
				 const std::string_view&& name,
				 const std::string_view&& description = "",
				 const bool optional = false) : Parameter(name, description, optional) { };
	constexpr int getType() override;
	constexpr BigFloat getDefaultValue() override;
};

