#include "ParameterVoid.h"

constexpr int ParameterVoid::getType() {
	return ParameterType::VOID_E;
}

constexpr void ParameterVoid::getDefaultValue() {
	return;
}
