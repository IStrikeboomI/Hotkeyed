#pragma once
#include "Parameter.h"
#include "../../lib/BigFloat/BigFloat.h"
class ParameterNum : public Parameter<BigFloat> {
public:
	ParameterNum(const std::string_view& type,
				 const std::string&& name,
				 const std::string&& description = "",
				 const bool optional = false) : Parameter(name,description,optional);
	constexpr int getType() override;
	constexpr BigFloat getDefaultValue() override;
};

