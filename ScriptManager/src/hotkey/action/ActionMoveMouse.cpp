#include "ActionMoveMouse.h"

ActionMoveMouse::ActionMoveMouse() : Action("MoveMouse", DataTypes::VOID_E, {Parameter("x",DataTypes::NUM),
											                                 Parameter("y",DataTypes::NUM)}, "Moves mouse cursor to (x,y)") {

}

std::shared_ptr<DataType> ActionMoveMouse::execute(std::vector<std::shared_ptr<DataType>>& parameters) {
	BigFloat x = parameters[0]->getValue<BigFloat>();
	BigFloat y = parameters[1]->getValue<BigFloat>();
	SetCursorPos(x.toInt(), y.toInt());
	return std::make_shared<DataTypeVoid>(DataTypeVoid());
}

