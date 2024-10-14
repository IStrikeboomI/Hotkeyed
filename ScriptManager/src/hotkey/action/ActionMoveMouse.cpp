#include "ActionMoveMouse.h"

ActionMoveMouse::ActionMoveMouse() : Action("MoveMouse",{Parameter(ParameterType::NUM,"x"),
											 Parameter(ParameterType::NUM,"y") }) {

}

std::any ActionMoveMouse::execute(std::map<Parameter, std::any>& params) {
	BigFloat x = std::any_cast<int>(getParam("x", params));
	BigFloat y = std::any_cast<int>(getParam("y", params));
	SetCursorPos(x.toInt(), y.toInt());
	return true;
}
