#include "ActionMoveMouse.h"

ActionMoveMouse::ActionMoveMouse() : Action("MoveMouse", DataTypes::VOID_E, {Parameter("x",DataTypes::INTEGER),
											                                 Parameter("y",DataTypes::INTEGER)}, "Moves mouse cursor to (x,y)",CATEGORY_MOUSE) {

}

std::shared_ptr<DataType> ActionMoveMouse::execute(std::vector<std::shared_ptr<DataType>>& parameters) {
	int x = parameters[0]->getData<DataTypeInteger>()->value;
	int y = parameters[1]->getData<DataTypeInteger>()->value;
	SetCursorPos(x, y);
	return std::make_shared<DataTypeVoid>(DataTypeVoid());
}

