#include "ActionMoveMouse.h"

ActionMoveMouse::ActionMoveMouse() : Action("MoveMouse",{Parameter(ParameterType::INT,"x"),
											 Parameter(ParameterType::INT,"y") }) {

}

std::any ActionMoveMouse::execute(std::map<Parameter, std::any>& params) {
	BigInt x = std::any_cast<int>(getParam("x", params));
	BigInt y = std::any_cast<int>(getParam("y", params));
	SetCursorPos(x.to_int(), y.to_int());
	return true;
}
