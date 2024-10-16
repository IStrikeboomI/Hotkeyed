#include "ParameterNum.h"

constexpr int ParameterNum::getType() {
	return ParameterType::NUM;
}

constexpr BigFloat ParameterNum::getDefaultValue() {
	return BigFloat();
}
