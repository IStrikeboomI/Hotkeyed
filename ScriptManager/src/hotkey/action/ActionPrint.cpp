#include "ActionPrint.h"

ActionPrint::ActionPrint() : Action("Print", DataTypes::VOID_E, {Parameter("text",DataTypes::STRING_E)}, "Prints text to console",
									CATEGORY_MISC | CATEGORY_DEBUG) {
}

std::shared_ptr<DataType> ActionPrint::execute(std::vector<std::shared_ptr<DataType>>& parameters) {
	std::cout << parameters[0]->getData<DataTypeString>()->value;
	return std::make_shared<DataTypeVoid>(DataTypeVoid());
}
