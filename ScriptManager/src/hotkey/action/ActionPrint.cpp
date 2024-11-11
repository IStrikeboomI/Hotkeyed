#include "ActionPrint.h"

ActionPrint::ActionPrint() : Action("Print", DataTypes::VOID_E, {Parameter("text",DataTypes::STRING)}) {
}

std::shared_ptr<DataType> ActionPrint::execute(std::vector<std::shared_ptr<DataType>>& parameters) {
	std::cout << parameters[0]->getValue<std::string>();
	return std::make_shared<DataTypeVoid>(DataTypeVoid());
}
