#include "MoveMouse.h"

MoveMouse::MoveMouse() : Action("MoveMouse",{Parameter(ParameterType::INT,"x"),
											 Parameter(ParameterType::INT,"y") }) {

}

std::any MoveMouse::execute(std::map<Parameter, std::any>& params) {
	int x = std::any_cast<int>(getParam("x", params));
	int y = std::any_cast<int>(getParam("y", params));
	SetCursorPos(x, y);
	return true;
}
